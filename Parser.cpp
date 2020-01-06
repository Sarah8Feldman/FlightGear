
//
// Created by adi on 24/12/2019.
//

#include "Parser.h"
#include <iostream>

using namespace std;

/**
 * add variables of the parser
 * @param vecParser  vector
 * @param index index in vector
 */
void Parser::addVaribles(vector<string> vecParser, int index){
this->vecParser = vecParser;
this->index = index;
}

/**
 * interpreter os a vector
 * 1. check if index is in command map
 * 2.create the command and execute
 */
void Parser::parse() {
    this->index = 0;
    string currentCommand;
    //execute only if it is a command.
    while (index < this->vecParser.size()) {
        currentCommand = this->vecParser[index];
        //It is not a command. continue to next iteration.
        if (this->commandMap.find(currentCommand) == commandMap.end()) {
            index =  DefineVarCommand(vecParser, index).execute();
        }
        //It's a command. index moved as many as the command args.
        Command *command = this->commandMap.find(currentCommand)->second;
        index = command->execute();
    }
}