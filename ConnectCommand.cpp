//
// Created by adi on 24/12/2019.
//

#include "ConnectCommand.h"

ConnectCommand::ConnectCommand() {}

void ConnectCommand::execute() {
    try {
        ExpressionManager em;
        string arg1 = *it;
        it++;
        double arg2 = em.calculate(it, args);
        if (it != args.end() || arg2 <= 0 || (int)arg2 != arg2) {
            throw "";
        }
        createClient(arg1, (int)arg2);
    } catch (...) {
        throw "invalid number of arguments for openDataServer";
    }

}

ConnectCommand::~ConnectCommand() {}
