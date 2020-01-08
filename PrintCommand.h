//
// Created by adi on 02/01/2020.
//

#ifndef STONEROAD1EX3_PRINTCOMMAND_H
#define STONEROAD1EX3_PRINTCOMMAND_H

#include "Command.h"
#include <string>
#include "Expression.h"
#include "ex1.h"
#include <vector>
#include "ExpressionCommand.h"

class PrintCommand : public Command {
private:
    double value;
    Expression* exp;
    vector<string> vecPrint;
    int index;
public:
    PrintCommand(vector<string> vecPrint);
//    void to_string(string &value);
    int execute(int index);
    virtual ~PrintCommand();
};


#endif //STONEROAD1EX3_PRINTCOMMAND_H
