//
// Created by sarah on 03/01/2020.
//
#include "SymbolTable.h"
#include <cstring>
#include <unistd.h>
#include <iostream>
//
///**
// * this map updates from the server
// * @param values vector from the buffer
// */
//void SymbolTable::updatePathValue(vector<double> values) {
//    pthread_mutex_t.lock();
//
//    pthread_mutex_t.unlock();
//}

/**
 * update the name->path in simulator map
 * @param name of variable
 * @param path variables path
 */
void SymbolTable::updateNameToPath(std::__cxx11::string name, std::__cxx11::string path) {
    pthread_mutex_t.lock();
    nameToPath[name] = path;
    //if name isn't in xml
    if(pathsToValue.count(path) == 0){
        pathsToValue[path] = 0;
    }
    pthread_mutex_t.unlock();
}
/**
 * update the map of the variables that are not from\in the simulator
 * @param name of variable
 * @param val its value
 */
void SymbolTable::updateVaresWithoutPath(string name, string val){
    if(nameToPath.count(val) == 0) {
        varesWithoutPath[name] = val;
    } else{
        varesWithoutPath[name] = pathsToValue.at(nameToPath[val]);
    }
}
/**
 * destructor
 */
SymbolTable::~SymbolTable() {}

//unordered_map<string, Command*> SymbolTable::getCommandMap() {
//    return *allCommandsrMap;
//}
