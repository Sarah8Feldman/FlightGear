//
// Created by adi on 22/12/2019.
//

#ifndef STONEROAD1EX3_COMMAND_H
#define STONEROAD1EX3_COMMAND_H

#include <string>
#include <vector>
#include <list>

using namespace std;

class Command {
public:
    virtual int execute(int index) = 0;
    virtual ~Command(){}
};

#endif //STONEROAD1EX3_COMMAND_H