//
// Created by adi on 24/12/2019.
//

#include "Parser.h"
#include "DefineVarCommand.h"
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
//        cout << "currentCommand is " << currentCommand << endl;
        //It is not a command. continue to next iteration.
        if (myTable->allCommandsMap.find(currentCommand) == myTable->allCommandsMap.end()) {
//            cout << "currentCommand is " << currentCommand << endl;
            index =  DefineVarCommand(vecParser).execute(index);
        } else {
            //It's a command. index moved as many as the command args.
            Command *command = myTable->allCommandsMap.find(currentCommand)->second;
            index = command->execute(index);
        }
    }
}