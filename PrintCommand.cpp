//
// Created by adi on 02/01/2020.
//

#include <iostream>
#include "PrintCommand.h"

PrintCommand::PrintCommand(vector<string> vecPrint, int index) {
    this->vecPrint = vecPrint;
    this->index = index;
}

int PrintCommand::execute() {
//    cout<<value->toString()<<endl;
    string str = this->vecPrint.at(index + 1);
    bool isString;
    //if string then print it without the quotes.
    //34 is " in ascii
    string temp = "";
    if (str.at(0) == 34) {
        for (int i = 1; i < str.length() - 1; i++) {
            temp += str.at(i);
        }
        cout << temp << endl;
        //convert the string to an Expression and print it if a legal one.
    } else {
        double exp = ExpressionCommand::interpertExpression(str);
        cout << exp << endl;
    }
    return index + 2;
}

PrintCommand::~PrintCommand() {}