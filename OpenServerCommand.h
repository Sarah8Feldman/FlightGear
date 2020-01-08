//
// Created by adi on 03/01/2020.
//

#ifndef STONEROAD1EX3_OPENSERVERCOMMAND_H
#define STONEROAD1EX3_OPENSERVERCOMMAND_H

#include "Command.h"
#include "SymbolTable.h"

class OpenServerCommand : public Command {
private:
    vector<string> vecOpenServer;
    string port;
    mutex myMutex;

public:
    OpenServerCommand(vector<string> vecOpenServer);
    int execute(int index);
    virtual ~OpenServerCommand();
    void runThread();
    string bufferToString(char *buff);
    vector<double> stringToVector(string str);
    bool regexMatches(string str);
    vector<string> regexer(string str, string pattern);
    void updateMap(vector<double> values);

    void runThread(int client_socket);

    vector<double> stringToDoubleVector(string str);
};


#endif //STONEROAD1EX3_OPENSERVERCOMMAND_H
