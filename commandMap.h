//
// Created by sarah on 02/01/2020.
//

#ifndef LEXER_COMMANDMAP_H
#define LEXER_COMMANDMAP_H

#include <unordered_map>
#include <string>
#include <vector>
#include "Command.h"

using namespace std;

class commandMap {
private:
    vector<string> vect;
    int index;
    unordered_map<string, Command*> varMap;
public:
    unordered_map<string, Command*> getCommandsMap();
    virtual ~commandMap();
};


#endif //LEXER_COMMANDMAP_H
