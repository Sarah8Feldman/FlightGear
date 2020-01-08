//
// Created by sarah on 03/01/2020.
//

#ifndef LEXER_DEFINEVARCOMMAND_H
#define LEXER_DEFINEVARCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"
#include "unordered_map"
#include "ex1.h"
#include <string>
#include "ExpressionCommand.h"
#include "commandMap.h"

class DefineVarCommand: public Command{
private:
    vector<string> vecDefine;

public:
    DefineVarCommand(vector<string> vecDefine);
    int execute(int index);
    virtual ~DefineVarCommand();

};


#endif //LEXER_DEFINEVARCOMMAND_H
