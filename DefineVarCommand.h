//
// Created by sarah on 03/01/2020.
//

#ifndef LEXER_DEFINEVARCOMMAND_H
#define LEXER_DEFINEVARCOMMAND_H

#include "Command.h"
#include "Var.h"
#include "SymbolTable.h"
#include "unordered_map"
#include "ex1.h"
#include <string>
#include "ExpressionCommand.h"
extern SymbolTable myTable;

class DefineVarCommand:Command{
private:
    vector<string> vec;
    int index;
    ExpressionCommand expressionC;

public:
    DefineVarCommand(vector<string> vect, int index);
    int execute();

};


#endif //LEXER_DEFINEVARCOMMAND_H
