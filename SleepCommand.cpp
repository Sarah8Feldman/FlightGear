//
// Created by adi on 31/12/2019.
//

#include "SleepCommand.h"
#include <chrono>
#include <thread>
/**
 * this commans sends thread to sleep for a spesific time
 * @param vecSleep vector
 * @param index index in vector
 */
SleepCommand::SleepCommand(vector<string> vecSleep, int index) {
    this->vecSleep = vecSleep;
    this->index = index;
    this->time = vecSleep[index + 1];
}
/**
 * check if time is valid string
 * @param vecString vector
 * @return true if is valid
 */
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
/**
 *
 * @return  the index of the next command
 */
int SleepCommand::execute() {
    if (checkIfValid(vector<string> {time})) {
        //simplify time if its an expression
        int myTime = ExpressionCommand::interpertExpression(time);
        this->milliseconds = myTime;
    } else {
        throw "invalid Sleep Command";
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(this->milliseconds));
    return index + 2;
}
/**
 * destructor
 */
SleepCommand::~SleepCommand() {}
