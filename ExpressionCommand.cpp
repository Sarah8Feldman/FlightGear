//
// Created by sarah on 05/01/2020.
//

#include "ExpressionCommand.h"

double ExpressionCommand::interpertExpression(string str){
    Interpreter interpreter;
    auto it = myTable->nameToPath.begin();
    int i = 0;
    for (it; it != myTable->nameToPath.end(); it++){
        interpreter.setVariables(it->first + "=" + myTable->pathsToValue[it->second]);
    }
    return interpreter.interpret(str)->calculate();
}