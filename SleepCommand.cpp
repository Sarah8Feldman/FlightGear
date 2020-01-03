//
// Created by adi on 31/12/2019.
//

#include "SleepCommand.h"
#include <chrono>
#include <thread>

SleepCommand::SleepCommand(vector<string> vecSleep, int index) {
    this->vecSleep = vecSleep;
    this->index = index;
    this->time = vecSleep[index + 1];
}

bool checkIfValid(vector<string> vecString) {
    try {
        if (vecString.size() != 1) {
            return false;
        } else {
            return (stoi(vecString[0]) >= 0);
        }
    } catch (...) {
        return false;
    }
}

void SleepCommand::execute() {
    if (checkIfValid(vector<string> {time})) {
        this->milliseconds = stoi(time);
    } else {
        throw "invalid Sleep Command";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(this->milliseconds));
}

SleepCommand::~SleepCommand() {}
