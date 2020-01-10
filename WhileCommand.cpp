//
// Created by sarah on 02/01/2020.
//
#include "WhileCommand.h"
#include "SymbolTable.h"
#include "DefineVarCommand.h"

/**
 * The While class represent a while loop.
 * To execute: if the condition is valid execute all of the commands inside the scope.
 * @param vect1 vector from lexer
 */
WhileCommand::WhileCommand(vector<string> vect1) {
    this->vect = vect1;
    globalMaps = SymbolTable::getInstance();
}

/**
 * This function checks if the condition is true.
 * @param index of this command in the lexer vector
 * @return true if condition is valid
 */
bool WhileCommand::checkCondition(int index) {
    //    in fly.txt
//     while name < value
//index  0    1   2   3
    string left = vect[index + 1];
    string op = vect[index + 2];
    string right = vect[index + 3];

    //simplify an expression and return its value
    double leftExp = ExpressionCommand::interpertExpression(left);
    double rightExp = ExpressionCommand::interpertExpression(right);

    //checks the condition
    if(op == ">"){
        if( leftExp > rightExp){
            return true;
        }
    }
    else if(op == ">="){
        if( leftExp >= rightExp){
            return true;
        }
    }
    else if(op == "<"){
        if( leftExp < rightExp){
            return true;
        }
    }
    else if(op == "<="){
        if( leftExp <= rightExp){
            return true;
        }
    }
    else if(op == "==") {
        if( leftExp == rightExp){
            return true;
        }
    }
    else if(op == "!="){
        if( leftExp != rightExp){
            return true;
        }
    }
    return false;
}

/**
 * If the condition is valid execute all of the commands inside the scope.
 * @param index of this command in the lexer vector
 * @return the next command index
 */
int WhileCommand::execute(int index) {
    int i = index + 5;
    while (checkCondition(index)) {
        auto vars = globalMaps->allCommandsMap;
        //while inside the scope
        string str = vect[i];
        while (vect[i] != "}") {
            auto it =  globalMaps->allCommandsMap.find(vect[i]);
            if (it !=  globalMaps->allCommandsMap.end()){
                i =  globalMaps->allCommandsMap.at(vect[i])->execute(i);
            } else {
                i =  DefineVarCommand(vect).execute(i);
            }
        }
        i = index + 5;
    }
    return i;
}
/**
 * destructor
 */
WhileCommand::~WhileCommand(){}