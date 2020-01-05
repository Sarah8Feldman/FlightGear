//
// Created by adi on 03/01/2020.
//

#ifndef STONEROAD1EX3_OPENSERVERCOMMAND_H
#define STONEROAD1EX3_OPENSERVERCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"
extern SymbolTable* myTable;

class OpenServerCommand : public Command {
private:
    vector<string> vecOpenServer;
    int index;
    string iP;
    string sim;

public:
    OpenServerCommand(vector<string> vecOpenServer, int index);
    int execute();
    virtual ~OpenServerCommand();
    void runThread();
    string bufferToString(char *buff);
    vector<string> stringToVector(string str);
};


#endif //STONEROAD1EX3_OPENSERVERCOMMAND_H
