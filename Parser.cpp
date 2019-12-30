//
// Created by adi on 24/12/2019.
//

#include "Parser.h"
#include "Interpreter.h"
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


Parser::Parser() {}

void Parser::execute() {
    Parser::commandMap = {
            {"openDataServer", new OpenServerCommandFactory()},
            {"connect", new ConnectCommandFactory()},
            {"var", new VarCommandFactory()},
            {"if", new IfCommandFactory()},
            {"while", new WhileCommandFactory()},
            {"sleep", new SleepCommandFactory()},
            {"print", new PrintCommandFactory()}

    };
}

void Parser::parser(list<string> elements) {
    list<string>::iterator it = elements.begin();
    Command* currentCommand;
    while (it != elements.end()) {
        currentCommand = Interpreter::getParser().getCommandFromString(*it);
        if (currentCommand == nullptr) {
            if (ToolBox::getSymbolTable().getVariable(*it) != nullptr) {
                currentCommand = new SetVarCommand();
            } else {
                throw "Not Valid Command " + *it;
            }
        } else {
            it++;
        }
        currentCommand->doCommand(it, elements);
        delete currentCommand;
    }
}

Parser::~Parser() {}