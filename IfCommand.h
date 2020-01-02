//
// Created by sarah on 31/12/2019.
//

#ifndef LEXER_IFCOMMAND_H
#define LEXER_IFCOMMAND_H
#include "Command.h"
#include "ex1.h"
#include "VarMap.h"
#include "unordered_map"
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
