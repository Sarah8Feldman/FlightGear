//
// Created by adi on 31/12/2019.
//

#ifndef STONEROAD1EX3_SLEEPCOMMAND_H
#define STONEROAD1EX3_SLEEPCOMMAND_H

#include "Command.h"
#include <vector>

class SleepCommand : public Command {
private:
    int milliseconds;
    vector<string> vecSleep;
    string time;
    int index;

public:
    SleepCommand(vector<string> vecSleep, int index);
    int execute();
    bool checkIfValid(vector<string> vecString);
    virtual ~SleepCommand();

};


#endif //STONEROAD1EX3_SLEEPCOMMAND_H
