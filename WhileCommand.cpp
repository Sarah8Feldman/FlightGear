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
    double leftExp = interpreter.interpret(left)->calculate();
    double rightExp = interpreter.interpret(right)->calculate();
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
    if (checkCondition()) {
        unordered_map<string, Command*>::iterator it;
        VarMap map;
        unordered_map<string, Command*> vars = map.getVarMap();
        int i = index + 5;
        while (vect[i] != "}") {
            it = vars.find(vect[i]);
            if (it != vars.end()){
                vars.at(vect[i])->execute();
            }
            i++;
        }
    }
}
