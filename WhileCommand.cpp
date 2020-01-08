//
// Created by sarah on 02/01/2020.
//
#include "WhileCommand.h"
#include "SymbolTable.h"

/**
 * This command inrerprates a while loop
 * @param vect1 vector
 * @param index1 index in vector
 */
WhileCommand::WhileCommand(vector<string> vect1) {
    this->vect = vect1;
}
/**
 * checks if the condition is true
 * @return true if condition is valid
 */
bool WhileCommand::checkCondition(int index) {
    //    if fly.txt
//    while name < value
//index 0    1  2  3
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
 * if the condition is valid execute all of the commands inside the scope
 * @return the next command index
 */
int WhileCommand::execute(int index) {
    int i = index + 5;
    while (checkCondition(index)) {
        unordered_map<string, Command*>::iterator it;

        auto vars = myTable->allCommandsMap;
        //while inside the scope
        while (vect[i] != "}") {
            it = vars.find(vect[i]);
            if (it != vars.end()){
                vars.at(vect[i])->execute(i);
            }
            i++;
        }
    }
    return i;
}
/**
 * destructor
 */
WhileCommand::~WhileCommand(){}