//
// Created by adi on 03/01/2020.
//

#ifndef STONEROAD1EX3_OPENSERVERCOMMAND_H
#define STONEROAD1EX3_OPENSERVERCOMMAND_H

#include "Command.h"
#include "Parser.h"

class OpenServerCommand : public Command {
private:
    vector<string> vecOpenServer;
    int index;
    string iP;
    string sim;

public:
    OpenServerCommand(vector<string> vecOpenServer, int index, string sim);
    int execute();
    virtual ~OpenServerCommand();

};


#endif //STONEROAD1EX3_OPENSERVERCOMMAND_H
