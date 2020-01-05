//
// Created by adi on 24/12/2019.
//

#ifndef STONEROAD1EX3_CONNECTCOMMAND_H
#define STONEROAD1EX3_CONNECTCOMMAND_H

#include "Command.h"
#include "ExpressionCommand.h"
#include "Parser.h"
extern SymbolTable* myTable;

class ConnectCommand : public Command {
private:
    vector<string> vecConnect;
    int index;
    string iP;
    string sim;

public:
    ConnectCommand(vector<string> vecConnect, int index);
    int execute();
    virtual ~ConnectCommand();

    Void runThread();
};



#endif //STONEROAD1EX3_CONNECTCOMMAND_H
