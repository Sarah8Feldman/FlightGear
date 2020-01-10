//
// Created by sarah on 03/01/2020.
//

#ifndef LEXER_DEFINEVARCOMMAND_H
#define LEXER_DEFINEVARCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"
#include "unordered_map"
#include "ExpressionInterpreter.h"
#include <string>
#include "ExpressionCommand.h"

/**
 * DefineVarCommand:
 * Inherits from Command interface and implements it.
 **/
class DefineVarCommand: public Command{
private:
    vector<string> vecDefine;

public:
    SymbolTable *globalMaps;

    DefineVarCommand(vector<string> vecDefine);

    int execute(int index);

    virtual ~DefineVarCommand();

    void updateMapForExpressionInterpreter(string name, string value);
};


#endif //LEXER_DEFINEVARCOMMAND_H
