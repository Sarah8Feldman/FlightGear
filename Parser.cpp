//
// Created by adi on 24/12/2019.
//

#include "Parser.h"
#include "DefineVarCommand.h"
#include <iostream>

using namespace std;
/**
 * Constructor
 */
Parser::Parser(){
    //an instanse of the singleton maps class
    globalMaps = SymbolTable::getInstance();
}
/**
 * The function add variables of the parser.
 * @param vecParser  vector from the lexer
 * @param index index in vector
 */
void Parser::addVaribles(vector<string> vecParser, int index){
    this->vecParser = vecParser;
    this->index = index;
}

/**
 * Interpreter os a vector.
 * 1. check if index is in command map
 * 2. create the command and execute
 */
void Parser::parse() {
    this->index = 0;
    string currentCommand;
    //execute only if it is a command.
    while (index < this->vecParser.size()) {
        currentCommand = this->vecParser[index];
        //It is not a command. continue to next iteration.
        if (currentCommand == "}") {
            index++;

        } //command such as "warp=3200" are not in the command map, but are kind of a "DefineVarCommand"-
        else if ((globalMaps->allCommandsMap.find(currentCommand) == globalMaps->allCommandsMap.end())) {
            index =  DefineVarCommand(vecParser).execute(index);
        } else {
            //It's a command. index moved as many as the command args.
            Command *command = globalMaps->allCommandsMap.find(currentCommand)->second;
            index = command->execute(index);
        }
    }
}