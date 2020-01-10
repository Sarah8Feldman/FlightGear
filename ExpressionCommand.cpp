//
// Created by sarah on 05/01/2020.
//

#include "ExpressionCommand.h"
#include "SymbolTable.h"

/**
 * ExpressionCommand class is a constructor.
 * get instance of singleton class.
 */
ExpressionCommand::ExpressionCommand() {
    globalMaps = SymbolTable::getInstance();
}

/**
 * This command simplify an expression
 * @param str string that is the expression
 * @return the expression final value (in double)
 */
double ExpressionCommand::interpertExpression(string str){
    return  SymbolTable::getInstance()->interpreter.interpret(str)->calculate();
}
/**
 * destructor
 */
ExpressionCommand::~ExpressionCommand() {}