//
// Created by adi on 24/12/2019.
//

#ifndef STONEROAD1EX3_CONNECTCOMMAND_H
#define STONEROAD1EX3_CONNECTCOMMAND_H

#include "Command.h"
#include "Parser.h"

class ConnectCommand : public Command {
//    Parser* parser;
//    string theIpServer;
//    bool checkIfIpIsValid(const std::vector<std::string> &) const;


public:
//    ConnectCommand(Parser* newParser) : parser(newParser) {};
//    void execute(vector<string>::iterator &it);


    ConnectCommand();
    void execute(list<string>::iterator & it, list<string> & args);
    virtual ~ConnectCommand();

};



#endif //STONEROAD1EX3_CONNECTCOMMAND_H
