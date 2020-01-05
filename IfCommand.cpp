//
// Created by sarah on 02/01/2020.
//
#include "IfCommand.h"
IfCommand::IfCommand(vector<string> vect1, int index1) {
    this->vect = vect1;
    this->index = index1;
}
bool IfCommand::checkCondition() {
    //"if" = vect[index]
    string left = vect[index + 1];
    string op = vect[index + 2];
    string right = vect[index + 3];
    Interpreter interpreter;
    double leftExp = ExpressionCommand::interpertExpression(left);
    double rightExp = ExpressionCommand::interpertExpression(right);
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
int IfCommand::execute() {
//    if name < val   {
//i = 0   1   2   3   4
    int i = index + 5;
    if (checkCondition()) {
        unordered_map<string, Command*>::iterator it;
        commandMap map;
        unordered_map<string, Command*> vars = map.getCommandsMap();
        while (vect[i] != "}") {
            it = vars.find(vect[i]);
            if (it != vars.end()){
                vars.at(vect[i])->execute();
            }
            i++;
        }
    } return i;
}
IfCommand::~IfCommand(){}