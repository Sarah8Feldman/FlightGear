//
// Created by sarah on 02/01/2020.
//
#include "IfCommand.h"
#include "SymbolTable.h"

/**
 * This command inrerprates an if "loop"
 * @param vect1 vector from lexer
 */
IfCommand::IfCommand(vector<string> vect1) {
    this->vect = vect1;
    globalMaps = SymbolTable::getInstance();
}
/**
 * Checks if the condition is true
 * @return true if condition is valid
 */
bool IfCommand::checkCondition() {
//      in fly.txt:
//      if name < value
//index 0  1  2  3
    string left = vect[index + 1];
    string op = vect[index + 2];
    string right = vect[index + 3];

    //simplify an expression and return its value
    double leftExp = ExpressionCommand::interpertExpression(left);
    double rightExp = ExpressionCommand::interpertExpression(right);
    //checks the conditiond
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
 * The execute function.
 * If the condition is valid execute all of the commands inside the scope.
 * @param index of the command
 * @return the next command index
 */
int IfCommand::execute(int index) {
//    if name < val   {
//i = 0   1   2   3   4
    int i = index + 5;
    if (checkCondition()) {
        //while inside the scope
        while (vect[i] != "}") {
            //find the command in the command map and execute it
            auto it =  globalMaps -> allCommandsMap.find(vect[i]);
            if (it != globalMaps -> allCommandsMap.end()){
                i = globalMaps -> allCommandsMap.at(vect[i])->execute(i);
            }
    }
        i = index + 5;
    } return i;
}
/**
 * destructor
 */
IfCommand::~IfCommand(){}