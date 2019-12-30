//
// Created by adi on 25/12/2019.
//
#include "Interpreter.h"

//Interpreter::Interpreter(Parser* parser)
//{
//    this->parser = parser;
//}
//
//void Interpreter::interperate(vector<string> &values)
//{
//    vector<string>::iterator begin = values.begin();
//    vector<string>::iterator end = values.end();
//
//    // We will keep read command form code part until we will reach the end of the code
//    while ((begin != end) && (!begin.operator->()->empty()))
//    {
//        readLine(begin);
//
//        // If we get to a \n we will skip it to get to the next command
//        if (begin != end)
//        {
//            if (*begin == "\n") {
//                begin++;
//            }
//        }
//    }
//}

//void Interpreter:: readLine(vector<string>::iterator &it)
//{
//}

Interpreter::Interpreter() {}

void Interpreter::execute() {
    parser.execute();
}

//Lexer& Interpreter::getLexer() {
//    return lexer;
//}

Parser& Interpreter::getParser() {
    return parser;
}
