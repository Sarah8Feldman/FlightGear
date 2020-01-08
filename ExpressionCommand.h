//
// Created by sarah on 05/01/2020.
//

#ifndef LEXER_EXPRESSIONCOMMAND_H
#define LEXER_EXPRESSIONCOMMAND_H

#include "ex1.h"
#include "map"
#include <string>
#include <cstring>
#include <mutex>


class ExpressionCommand {
public:
    static double interpertExpression(string str);
    virtual ~ExpressionCommand();
};


#endif //LEXER_EXPRESSIONCOMMAND_H
