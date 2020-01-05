//
// Created by sarah on 02/01/2020.
//
#include "IfCommand.h"
/**
 * This command inrerprates an if "loop"
 * @param vect1 vector
 * @param index1 index in vector
 */
IfCommand::IfCommand(vector<string> vect1, int index1) {
    this->vect = vect1;
    this->index = index1;
}
/**
 * checks if the condition is true
 * @return true if condition is valid
 */
bool IfCommand::checkCondition() {
//    if fly.txt
//    if name < value
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
 * if the condition is valid execute all of the commands inside the scope
 * @return the next command index
 */
int IfCommand::execute() {
//    if name < val   {
//i = 0   1   2   3   4
    int i = index + 5;
    if (checkCondition()) {
        unordered_map<string, Command*>::iterator it;
        commandMap map;
        unordered_map<string, Command*> vars = map.getCommandsMap();
        //while inside the scope
        while (vect[i] != "}") {
            it = vars.find(vect[i]);
            if (it != vars.end()){
                vars.at(vect[i])->execute();
            }
            i++;
        }
    } return i;
}
/**
 * destructor
 */
IfCommand::~IfCommand(){}