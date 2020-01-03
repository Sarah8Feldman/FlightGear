//
// Created by adi on 02/01/2020.
//

#include <iostream>
#include "PrintCommand.h"

PrintCommand::PrintCommand(vector<string> vecPrint, int index) {
    this->vecPrint = vecPrint;
    this->index = index;
}

//string PrintCommand::to_string(double value) {
//    return to_string(value.call);
//}

void PrintCommand::execute() {
//    cout<<value->toString()<<endl;
    string str = this->vecPrint.at(value + 1);
    //if string then print it without the quotes.
    if (str.at(0) == 34) {
        string temp = "";
        for (int i = 1; i < str.length() - 1; i++) {
            temp += str.at(i);
        }
        cout << temp << endl;
        //convert the string to an Expression and print it if a legal one.
    } else {
        Interpreter interp;
        Expression *exp = interp.interpret(str);
        cout << exp->calculate() << endl;
        delete (exp);
    }
}

PrintCommand::~PrintCommand() {}