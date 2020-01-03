//
// Created by adi on 24/12/2019.
//

#ifndef STONEROAD1EX3_CONNECTCOMMAND_H
#define STONEROAD1EX3_CONNECTCOMMAND_H

#include "Command.h"
#include "Parser.h"

class ConnectCommand : public Command {
private:
    vector<string> vecCommand;
    int index;
    string iP;
    string sim;

public:
    ConnectCommand(vector<string> vecCommand, int index, string sim);

    int execute();
    virtual ~ConnectCommand();

};



#endif //STONEROAD1EX3_CONNECTCOMMAND_H
