//
// Created by adi on 03/01/2020.
//

#ifndef STONEROAD1EX3_OPENSERVERCOMMAND_H
#define STONEROAD1EX3_OPENSERVERCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"

/**
 * OpenServerCommand:
 * Inherits from Command interface and implements it.
 **/
class OpenServerCommand : public Command {
private:
    vector<string> vecOpenServer;

public:
    SymbolTable *globalMaps;

    OpenServerCommand(vector<string> vecOpenServer);

    int execute(int index);

    virtual ~OpenServerCommand();

    void updateMaps(vector<double> values);

    void runThread(int client_socket);

    vector<double> stringToDoubleVector(string str);

    void updateMapForExpressionInterpreter();

};


#endif //STONEROAD1EX3_OPENSERVERCOMMAND_H
