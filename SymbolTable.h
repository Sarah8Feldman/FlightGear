//
// Created by sarah on 03/01/2020.
//

#ifndef LEXER_SYMBOLTABLE_H
#define LEXER_SYMBOLTABLE_H

#include <unordered_map>
#include "deque"
#include "thread"
#include <vector>
#include <queue>
#include <mutex>
#include "Command.h"
using namespace std;


//THIS CLASS IS GLOBAL

class SymbolTable {
private:
    vector<string> values;
    mutex pthread_mutex_t;
    int socket;
public:

    queue<string> sendToServerQueue; //queue of values to update the simulator
    unordered_map<string,string> nameToPath; // map name->path in simulator
    unordered_map<string, string> varesWithoutPath; //map of variables that aren't in the simulator & values
    //map of path in simulator->values
    unordered_map<string, double> pathsToValue = {{"/instrumentation/airspeed-indicator/indicated-speed-kt", 0},
                                      {"/sim/time/warp", 0},
                                      {"/controls/switches/magnetos", 0},
                                      {"/instrumentation/heading-indicator/offset-deg", 0},
                                      {"/instrumentation/altimeter/indicated-altitude-ft", 0},
                                      {"/instrumentation/altimeter/pressure-alt-ft", 0},
                                      {"/instrumentation/attitude-indicator/indicated-pitch-deg", 0},
                                      {"/instrumentation/attitude-indicator/indicated-roll-deg", 0},
                                      {"/instrumentation/attitude-indicator/internal-pitch-deg", 0},
                                      {"/instrumentation/attitude-indicator/internal-roll-deg", 0},
                                      {"/instrumentation/encoder/indicated-altitude-ft", 0},
                                      {"/instrumentation/encoder/pressure-alt-ft", 0},
                                      {"/instrumentation/gps/indicated-altitude-ft", 0},
                                      {"/instrumentation/gps/indicated-ground-speed-kt", 0},
                                      {"/instrumentation/gps/indicated-vertical-speed", 0},
                                      {"/instrumentation/heading-indicator/indicated-heading-deg", 0},
                                      {"/instrumentation/magnetic-compass/indicated-heading-deg", 0},
                                      {"/instrumentation/slip-skid-ball/indicated-slip-skid", 0},
                                      {"/instrumentation/turn-indicator/indicated-turn-rate", 0},
                                      {"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0},
                                      {"/controls/flight/aileron", 0},
                                      {"/controls/flight/elevator", 0},
                                      {"/controls/flight/rudder", 0},
                                      {"/controls/flight/flaps", 0},
                                      {"/controls/engines/engine/throttle", 0},
                                      {"/controls/engines/current-engine/throttle", 0},
                                      {"/controls/switches/master-avionics", 0},
                                      {"/controls/switches/starter", 0},
                                      {"/engines/active-engine/auto-start", 0},
                                      {"/controls/flight/speedbrake", 0},
                                      {"/sim/model/c172p/brake-parking", 0},
                                      {"/controls/engines/engine/primer", 0},
                                      {"/controls/engines/current-engine/mixture", 0},
                                      {"/controls/switches/master-bat", 0},
                                      {"/controls/switches/master-alt", 0},
                                      {"/engines/engine/rpm", 0}


    };
    unordered_map<string, Command*> allCommandsMap;
    void updateNameToPath(string name, string path);
//    unordered_map<string, Command*> getCommandMap();
    void updatePathValue(vector<double > values);
    void updateVaresWithoutPath(string name, string val);
    virtual ~SymbolTable();

    //2 of our secondary threas
    thread clientTread;
    thread serverThread;

    bool serverIsUp = true;
};
//declare the symboltable to be global
extern SymbolTable* myTable;


#endif //LEXER_SYMBOLTABLE_H
