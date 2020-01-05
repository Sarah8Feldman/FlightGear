//
// Created by adi on 24/12/2019.
//

#ifndef STONEROAD1EX3_PARSER_H
#define STONEROAD1EX3_PARSER_H

#include "Command.h"
#include "Lexer.h"
#include "ConnectCommand.h"
#include "OpenServerCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "Expression.h"
#include "ex1.h"
#include "commandMap.h"
#include "DefineVarCommand.h"
#include "SymbolTable.h"
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <list>

class Parser : public Command {
private:
    vector<string> vecParser;
    int index;
    map<string, Command*> commandMap;
//    Command* getCommandFromString(string str);

public:
    commandMap mp;
    Parser(vector<string> vecParser, int index);
//    int execute();
    bool parser();
    virtual ~Parser();
};


#endif //STONEROAD1EX3_PARSER_H
