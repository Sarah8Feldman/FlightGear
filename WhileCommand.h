//
// Created by sarah on 31/12/2019.
//

#ifndef LEXER_WHILECOMMAND_H
#define LEXER_WHILECOMMAND_H
#include "Command.h"
#include "ExpressionInterpreter.h"
#include <unordered_map>
#include "ExpressionCommand.h"

/**
 * WhileCommand:
 * Inherits from Command interface and implements it.
 **/
class WhileCommand : public Command {
private:
    vector<string> vect;

    int index;

public:
    SymbolTable *globalMaps ;

    WhileCommand(vector<string> vect);

    int execute(int index);

    virtual ~WhileCommand();

    bool checkCondition(int index);
};

#endif //LEXER_WHILECOMMAND_H
