//
// Created by adi on 24/12/2019.
//

#ifndef STONEROAD1EX3_CONNECTCOMMAND_H
#define STONEROAD1EX3_CONNECTCOMMAND_H

#include "Command.h"
#include "ExpressionCommand.h"
#include "SymbolTable.h"
//#include "Parser.h"

/**
 * ConnectCommand:
 * Inherits from Command interface and implements it.
 **/
class ConnectCommand : public Command {
private:
    vector<string> vecConnect;
    int index;
    string iP;
    string port;
    string sim;

public:
    SymbolTable *globalMaps;

    ConnectCommand(vector<string> vecConnect);

    int execute(int index);

    virtual ~ConnectCommand();

    void runThread();

    void runThread(int clientSocket);
};



#endif //STONEROAD1EX3_CONNECTCOMMAND_H
