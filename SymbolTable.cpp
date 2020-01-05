//
// Created by sarah on 03/01/2020.
//
#include "SymbolTable.h"
#include <cstring>
#include <unistd.h>

/**
 * this map updates from the server
 * @param values vector from the buffer
 */
void SymbolTable::updatePathValue(vector<string> values) {
    pthread_mutex_lock(this->mutex);
    pathsToValue.at("/instrumentation/airspeed-indicator/indicated-speed-kt") = values [0];
    pathsToValue.at("/sim/time/warp") = values [1];
    pathsToValue.at("/controls/switches/magnetos") = values [2];
    pathsToValue.at("/instrumentation/heading-indicator/offset-deg") = values [3];
    pathsToValue.at("/instrumentation/altimeter/indicated-altitude-ft") = values [4];
    pathsToValue.at("/instrumentation/altimeter/pressure-alt-ft") = values [5];
    pathsToValue.at("/instrumentation/attitude-indicator/indicated-pitch-deg") = values [6];
    pathsToValue.at("/instrumentation/attitude-indicator/indicated-roll-deg") = values [7];
    pathsToValue.at("/instrumentation/attitude-indicator/internal-pitch-deg") = values [8];
    pathsToValue.at("/instrumentation/attitude-indicator/internal-roll-deg") = values [9];
    pathsToValue.at("/instrumentation/encoder/indicated-altitude-ft") = values [10];
    pathsToValue.at("/instrumentation/encoder/pressure-alt-ft") = values [11];
    pathsToValue.at("/instrumentation/gps/indicated-altitude-ft") = values [12];
    pathsToValue.at("/instrumentation/gps/indicated-ground-speed-kt") = values [13];
    pathsToValue.at("/instrumentation/gps/indicated-vertical-speed") = values [14];
    pathsToValue.at("/instrumentation/heading-indicator/indicated-heading-deg") = values [15];
    pathsToValue.at("/instrumentation/magnetic-compass/indicated-heading-deg") = values [16];
    pathsToValue.at("/instrumentation/slip-skid-ball/indicated-slip-skid") = values [17];
    pathsToValue.at("/instrumentation/turn-indicator/indicated-turn-rate") = values [18];
    pathsToValue.at("/instrumentation/vertical-speed-indicator/indicated-speed-fpm") = values [19];
    pathsToValue.at("/controls/flight/aileron") = values [20];
    pathsToValue.at("/controls/flight/elevator") = values [21];
    pathsToValue.at("/controls/flight/rudder") = values [22];
    pathsToValue.at("/controls/flight/flaps") = values [23];
    pathsToValue.at("/controls/engines/engine/throttle") = values [24];
    pathsToValue.at("/controls/engines/current-engine/throttle") = values [25];
    pathsToValue.at("/controls/switches/master-avionics") = values [26];
    pathsToValue.at("/controls/switches/starter") = values [27];
    pathsToValue.at("/engines/active-engine/auto-start") = values [28];
    pathsToValue.at("/controls/flight/speedbrake") = values [29];
    pathsToValue.at("/sim/model/c172p/brake-parking") = values [30]
    pathsToValue.at("/controls/engines/engine/primer") = values [31];
    pathsToValue.at("/controls/engines/current-engine/mixture") = values [32];
    pathsToValue.at("/controls/switches/master-bat") = values [33];
    pathsToValue.at("/controls/switches/master-alt") = values [34];
    pathsToValue.at("/engines/engine/rpm") = values [35];
    pthread_mutex_unlock(this->mutex);
}

/**
 * update the name->path in simulator map
 * @param name of variable
 * @param path variables path
 */
void SymbolTable::updateNameToPath(std::__cxx11::string name, std::__cxx11::string path) {
    pthread_mutex_lock(this->mutex);
    nameToPath[name] = path;
    //if name isn't in xml
    if(pathsToValue.count(path) == 0){
        pathsToValue[path] = 0;
    }
    pthread_mutex_unlock(this->mutex);
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
SymbolTable::~SymbolTable(){}
