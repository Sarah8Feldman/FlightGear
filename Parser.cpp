//
// Created by adi on 24/12/2019.
//

#include "Parser.h"
#include "InterpreterEx3.h"

#include <iostream>
using namespace std;


//Parser::Parser(Parser *newParser) {
//    parser = newParser;
//}
//
//void Parser::execute(vector<string>::iterator & it) {
//    vector<string> condition;
//    vector<string> InsideTheBrackets;
//    string newLine;
//    int counterBrackets = 0;
//    it++;
//    while (*it != "{") {
//        condition.push_back(*it);
//        it++;
//    }
//    counterBrackets++;
//    condition.push_back("\n");
//    it++;
//    if (*it != "\n") {
//        throw exception("Error: statement after opening bracket");
//    }
//}

map<string, Command*> Parser::commandMap;

Command* Parser::getCommandFromString(string str) {
    if (commandMap.count(str) == 0) {
        return nullptr;
    } else {
        return commandMap[str]->create();
    }
}


Parser::Parser(vector<string> vecParser, int index) {
    this->vecParser = vecParser;
    this->index = index;
}

int Parser::execute() {
    Parser::commandMap = {
            {"openDataServer", new OpenServerCommand()},
            {"connect", new ConnectCommand()},
            {"var", new VarCommand},
            {"if", new IfCommand()},
            {"while", new WhileCommand()},
            {"sleep", new SleepCommand()},
            {"print", new PrintCommand()}

    };
}

void Parser::parser(list<string> elements) {
    list<string>::iterator iterStart = elements.begin();
    Command* currentCommand;
    while (iterStart != elements.end()) {
        currentCommand = InterpreterEx3::getParser().getCommandFromString(*iterStart);
        if (currentCommand == nullptr) {
            if (ToolBox::getSymbolTable().getVariable(*iterStart) != nullptr) {
                currentCommand = new SetVarCommand();
            } else {
                throw "Not Valid Command " + *iterStart;
            }
        } else {
            iterStart++;
        }
        currentCommand->execute(iterStart, elements);
        delete currentCommand;
    }
}

Parser::~Parser() {}