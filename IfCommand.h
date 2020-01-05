//
// Created by sarah on 31/12/2019.
//

#ifndef LEXER_IFCOMMAND_H
#define LEXER_IFCOMMAND_H
#include "Command.h"
#include "ex1.h"
#include "commandMap.h"
#include "unordered_map"
#include "ExpressionCommand.h"
extern SymbolTable* myTable;

class IfCommand:Command {
private:
    vector<string> vect;
    int index;

public:
    IfCommand(vector<string> vect, int index);
     virtual int execute();
    virtual ~IfCommand();
    bool checkCondition();
};


#endif //LEXER_IFCOMMAND_H
