//
// Created by sarah on 31/12/2019.
//

#ifndef LEXER_WHILECOMMAND_H
#define LEXER_WHILECOMMAND_H
#include "Command.h"
#include "ex1.h"
#include "commandMap.h"
#include "unordered_map"
#include "ExpressionCommand.h"
extern SymbolTable* myTable;

class WhileCommand : Command {
private:
    vector<string> vect;
    int index;

public:
    WhileCommand(vector<string> vect, int index);
    virtual int execute();
    virtual ~WhileCommand();
    bool checkCondition();

};

#endif //LEXER_WHILECOMMAND_H
