//
// Created by sarah on 05/01/2020.
//

#include "ExpressionCommand.h"
#include "SymbolTable.h"

/**
 * this command simplify an expression
 * @param str string that is the expression
 * @return the expression final value
 */
double ExpressionCommand::interpertExpression(string str){
    Interpreter interpreter;
    auto it = myTable->nameToPath.begin();
    int i = 0;
    //set all of the variables from simulator so that the interpreter can use them as variables
    for (it; it != myTable->nameToPath.end(); it++){
        string command = it->first + "=" + to_string(myTable->pathsToValue.at(it->second)) + ";";
        interpreter.setVariables(command);

    }
    //calculate the expression
    return interpreter.interpret(str)->calculate();
}
/**
 * destructor
 */
ExpressionCommand::~ExpressionCommand() {}