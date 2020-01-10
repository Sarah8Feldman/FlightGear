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
#include <map>
#include "Command.h"
#include "ExpressionInterpreter.h"

using namespace std;


//THIS CLASS IS A SINGLETON

/**
 * The Symbol Table Class holes all of our maps and single cladd declerations
 */
class SymbolTable {
private:
    static SymbolTable* instance;

public:
    static SymbolTable* getInstance();
    mutex gMutex;
    queue<string> clientCommandsQueue; //queue of values to update the simulator

    unordered_map<string,string> nameToPathMap; // map name->path in simulator

    unordered_map<string, string> varsWithoutPathMap; //map of variables that aren't in the simulator & values

    unordered_map<string, string> pathToArrowDir; // map of arrow diractions: -> or <- to paths ion the simulator

    //map of path in simulator->values
    //all paths are from generic_small.xml file
    unordered_map<string, double> pathsToValueMap = {{"/instrumentation/airspeed-indicator/indicated-speed-kt",  0},
                                                     {"/sim/time/warp",                                          0},
                                                     {"/controls/switches/magnetos",                             0},
                                                     {"/instrumentation/heading-indicator/offset-deg",           0},
                                                     {"/instrumentation/altimeter/indicated-altitude-ft",        0},
                                                     {"/instrumentation/altimeter/pressure-alt-ft",              0},
                                                     {"/instrumentation/attitude-indicator/indicated-pitch-deg", 0},
                                                     {"/instrumentation/attitude-indicator/indicated-roll-deg",  0},
                                                     {"/instrumentation/attitude-indicator/internal-pitch-deg",  0},
                                                     {"/instrumentation/attitude-indicator/internal-roll-deg",   0},
                                                     {"/instrumentation/encoder/indicated-altitude-ft",          0},
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

    //a map of all insexes to the pathes of the simulator
    //the index are the order of paths from generic_small.xml file
    unordered_map<int, string> indexToPath =  {{1, "/instrumentation/airspeed-indicator/indicated-speed-kt"},
                                                    {2, "/sim/time/warp"},
                                                    {3, "/controls/switches/magnetos"},
                                                    {4, "/instrumentation/heading-indicator/offset-deg"},
                                                    {5, "/instrumentation/altimeter/indicated-altitude-ft"},
                                                    {6, "/instrumentation/altimeter/pressure-alt-ft"},
                                                    {7, "/instrumentation/attitude-indicator/indicated-pitch-deg"},
                                                    {8, "/instrumentation/attitude-indicator/indicated-roll-deg"},
                                                    {9, "/instrumentation/attitude-indicator/internal-pitch-deg"},
                                                    {10, "/instrumentation/attitude-indicator/internal-roll-deg"},
                                                    {11, "/instrumentation/encoder/indicated-altitude-ft"},
                                                    {12, "/instrumentation/encoder/pressure-alt-ft"},
                                                    {13, "/instrumentation/gps/indicated-altitude-ft"},
                                                    {14, "/instrumentation/gps/indicated-ground-speed-kt"},
                                                    {15, "/instrumentation/gps/indicated-vertical-speed"},
                                                    {16, "/instrumentation/heading-indicator/indicated-heading-deg"},
                                                    {17, "/instrumentation/magnetic-compass/indicated-heading-deg"},
                                                    {18, "/instrumentation/slip-skid-ball/indicated-slip-skid"},
                                                    {19, "/instrumentation/turn-indicator/indicated-turn-rate"},
                                                    {20, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm"},
                                                    {21, "/controls/flight/aileron"},
                                                    {22, "/controls/flight/elevator"},
                                                    {23, "/controls/flight/rudder"},
                                                    {24, "/controls/flight/flaps"},
                                                    {25, "/controls/engines/engine/throttle"},
                                                    {26, "/controls/engines/current-engine/throttle"},
                                                    {27, "/controls/switches/master-avionics"},
                                                    {28, "/controls/switches/starter"},
                                                    {29, "/engines/active-engine/auto-start"},
                                                    {30, "/controls/flight/speedbrake"},
                                                    {31, "/sim/model/c172p/brake-parking"},
                                                    {32, "/controls/engines/engine/primer"},
                                                    {33, "/controls/engines/current-engine/mixture"},
                                                    {34, "/controls/switches/master-bat"},
                                                    {35, "/controls/switches/master-alt"},
                                                    {36, "/engines/engine/rpm"}};

    unordered_map<string, Command*> allCommandsMap; // a map of all of our command

    void updateNameToPath(string name, string path);

    void updateVaresWithoutPath(string name, string val);

    virtual ~SymbolTable();

    //an global instance of cladd interpreter
    Interpreter interpreter;

};

#endif //LEXER_SYMBOLTABLE_H
