//
// Created by sarah on 03/01/2020.
//
#include "SymbolTable.h"
#include <cstring>
#include <unistd.h>
#include <iostream>
SymbolTable* SymbolTable::instance = 0;
/**
 * from singleton design pattern- returns an instance of a class
 * if the instance hasn't been already creates - create a new class
 * @return
 */
SymbolTable* SymbolTable::getInstance() {
    if (!instance)
        instance = new SymbolTable;
    return instance;
}

/**
 * Update the name->path in simulator map.
 * @param name of variable
 * @param path variables path
 */
void SymbolTable::updateNameToPath(string name, string path) {
    gMutex.lock();
    nameToPathMap[name] = path;
    //if name isn't in xml
    if(pathsToValueMap.count(path) == 0 && !(isdigit(path[0]) || path[0] == '-')){
        pathsToValueMap[path] = 0;
    }
    gMutex.unlock();
}
/**
 * Update the map of the variables that are not from\in the simulator.
 * @param name of variable
 * @param val its value
 */
void SymbolTable::updateVaresWithoutPath(string name, string val) {
    if(nameToPathMap.count(val) == 0) {
        varsWithoutPathMap[name] = val;
    } else{
        varsWithoutPathMap[name] = pathsToValueMap.at(nameToPathMap[val]);
    }
}
/**
 * destructor
 */
SymbolTable::~SymbolTable() {}

