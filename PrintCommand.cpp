//
// Created by adi on 02/01/2020.
//

#include <iostream>
#include "PrintCommand.h"
/**
 * This command prints a value that it excepts.
 * @param vecPrint vector
 */
PrintCommand::PrintCommand(vector<string> vecPrint) {
    this->vecPrint = vecPrint;
    this->index = index;
}
/**
 * In the execute function we have 2 cases:
 * 1. print a string in between ""
 * 2. print a value of a variable(can be an expression)
 * @param index
 */
int PrintCommand::execute(int index) {
    string str = this->vecPrint.at(index + 1); //value to print

    //if string then print it without the quotes.
    string temp = "";
    if (str.at(0) == '"') {
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