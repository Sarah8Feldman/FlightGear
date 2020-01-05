//
// Created by sarah on 02/01/2020.
//

#ifndef LEXER_COMMANDMAP_H
#define LEXER_COMMANDMAP_H

#include <unordered_map>
#include "Command.h"
#include "IfCommand.h"
#include "WhileCommand.h"

class commandMap {
private:
    vector<string> vect;
    int index;
    unordered_map<string, Command*> varMap = {{"openDataServer", OpenServerCommand(vect, index)},
                                             {"connect",         ConnectCommand(vect, index)},
                                             {"var",             DefineVarCommand(vect, index)},
                                             {"if",              IfCommand(vect, index)},
                                             {"while",           WhileCommand(vect, index)},
                                             {"sleep",           SleepCommand(vect, index)},
                                             {"print",           PrintCommand(vect, index)}
    };
public:
    unordered_map<string, Command*> getCommandsMap();
};


#endif //LEXER_COMMANDMAP_H
