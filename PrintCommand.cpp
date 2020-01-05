//
// Created by adi on 02/01/2020.
//

#include <iostream>
#include "PrintCommand.h"
/**
 * this command prints a value that it excepts
 * @param vecPrint vector
 * @param index index in vector
 */
PrintCommand::PrintCommand(vector<string> vecPrint, int index) {
    this->vecPrint = vecPrint;
    this->index = index;
}
/**
 * we have 2 cases:
 * 1. print a string in between ""
 * 2. print a value of a variable(can be an expression)
 * @return the next command index
 */
int PrintCommand::execute() {
    string str = this->vecPrint.at(index + 1); //value to print
    //if string then print it without the quotes.
    //34 is "" in ascii
    string temp = "";
    if (str.at(0) == 34) {
        for (int i = 1; i < str.length() - 1; i++) {
            temp += str.at(i);
        }
        cout << temp << endl;

    } else { //convert the string to an Expression and print it if a legal one.
        double exp = ExpressionCommand::interpertExpression(str);
        cout << exp << endl;
    }
    return index + 2;
}
/**
 * destructor
 */
PrintCommand::~PrintCommand() {}