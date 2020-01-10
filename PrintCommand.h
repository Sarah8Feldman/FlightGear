//
// Created by adi on 02/01/2020.
//

#ifndef STONEROAD1EX3_PRINTCOMMAND_H
#define STONEROAD1EX3_PRINTCOMMAND_H

#include "Command.h"
#include <string>
#include "Expression.h"
#include "ExpressionInterpreter.h"
#include <vector>
#include "ExpressionCommand.h"

/**
 * PrintCommand:
 * Inherits from Command interface and implements it.
 **/
class PrintCommand : public Command {
private:
    double value;

    vector<string> vecPrint;

    int index;

public:
    PrintCommand(vector<string> vecPrint);

    int execute(int index);

    virtual ~PrintCommand();
};


#endif //STONEROAD1EX3_PRINTCOMMAND_H
