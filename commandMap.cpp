//
// Created by sarah on 02/01/2020.
//

#include "commandMap.h"
/**
 * get the command map - the map ia private to avoid changes
 * @return a map of the commands
 */
unordered_map<string, Command*> commandMap::getCommandsMap() {
    return varMap;
}
/**
 * distructore
 */
commandMap::~commandMap(){}
