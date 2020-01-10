//
// Created by sarah on 05/01/2020.
//

#ifndef LEXER_EXPRESSIONCOMMAND_H
#define LEXER_EXPRESSIONCOMMAND_H

#include "ExpressionInterpreter.h"
#include "map"
#include "SymbolTable.h"
#include <string>
#include <cstring>
#include <mutex>

/**
 * The Expression command simplify an expression using the expression interpreter(ex1).
 */
class ExpressionCommand {
public:
    ExpressionCommand();

    SymbolTable *globalMaps;

    static double interpertExpression(string str);

    virtual ~ExpressionCommand();

};


#endif //LEXER_EXPRESSIONCOMMAND_H
