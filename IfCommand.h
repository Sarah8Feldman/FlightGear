//
// Created by sarah on 31/12/2019.
//

#ifndef LEXER_IFCOMMAND_H
#define LEXER_IFCOMMAND_H
#include "ExpressionInterpreter.h"
#include "unordered_map"
#include "ExpressionCommand.h"
#include "Command.h"

/**
 * IfCommand:
 * Inherits from Command interface and implements it.
 **/
class IfCommand: public Command {
private:
    vector<string> vect;

    int index;

public:
    SymbolTable *globalMaps;

    IfCommand(vector<string> vect);

    int execute(int index);

    virtual ~IfCommand();

    bool checkCondition();
};


#endif //LEXER_IFCOMMAND_H
