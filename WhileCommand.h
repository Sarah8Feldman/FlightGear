//
// Created by sarah on 31/12/2019.
//

#ifndef LEXER_WHILECOMMAND_H
#define LEXER_WHILECOMMAND_H
#include "Command.h"
#include "ex1.h"
#include <unordered_map>
#include "ExpressionCommand.h"

class WhileCommand : public Command {
private:
    vector<string> vect;
    int index;

public:
    WhileCommand(vector<string> vect);
    int execute(int index);
    virtual ~WhileCommand();
    bool checkCondition();

    bool checkCondition(int index);
};

#endif //LEXER_WHILECOMMAND_H
