//
// Created by adi on 31/12/2019.
//

#ifndef STONEROAD1EX3_SLEEPCOMMAND_H
#define STONEROAD1EX3_SLEEPCOMMAND_H

#include "Command.h";

class SleepCommand : public Command {
    int milliseconds;

public:
    SleepCommand();
    void execute(vector<string> vecSleep, string &str);
    bool checkIfValid(vector<string> vecString);
    virtual ~SleepCommand();

};


#endif //STONEROAD1EX3_SLEEPCOMMAND_H
