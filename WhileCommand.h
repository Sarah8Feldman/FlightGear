//
// Created by sarah on 31/12/2019.
//

#ifndef LEXER_WHILECOMMAND_H
#define LEXER_WHILECOMMAND_H
#include "Command.h"
#include "ex1.h"
#include "VarMap.h"
#include "unordered_map"

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
