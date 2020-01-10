//
// Created by adi on 24/12/2019.
//

#ifndef STONEROAD1EX3_PARSER_H
#define STONEROAD1EX3_PARSER_H

#include "Command.h"
#include "Lexer.h"
#include "Expression.h"
#include "ExpressionInterpreter.h"
#include "SymbolTable.h"
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <list>

/**
 * The Parser Class.
 * this class is an interperter for flight commands
 */
class Parser {
private:
    vector<string> vecParser;

    int index;

public:
    Parser();

    SymbolTable *globalMaps;

    void parse();

    void addVaribles(vector<string> vecParser, int index);
};


#endif //STONEROAD1EX3_PARSER_H