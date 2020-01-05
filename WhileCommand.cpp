//
// Created by sarah on 02/01/2020.
//
#include "WhileCommand.h"
WhileCommand::WhileCommand(vector<string> vect1, int index1) {
    this->vect = vect1;
    this->index = index1;
}
bool WhileCommand::checkCondition() {
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
int WhileCommand::execute() {
    int i = index + 5;
    while (checkCondition()) {
        unordered_map<string, Command*>::iterator it;
        commandMap map;
        unordered_map<string, Command*> vars = map.getCommandsMap();
//        int i = index + 5;
        while (vect[i] != "}") {
            it = vars.find(vect[i]);
            if (it != vars.end()){
                vars.at(vect[i])->execute();
            }
            i++;
        }
    }
    return i;
}
