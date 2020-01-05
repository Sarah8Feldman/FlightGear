//
// Created by sarah on 02/01/2020.
//

#include "commandMap.h"
unordered_map<string, Command*> commandMap::getCommandsMap() {
    return varMap;
}
