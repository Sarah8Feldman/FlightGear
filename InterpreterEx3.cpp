//
// Created by adi on 25/12/2019.
//
#include "InterpreterEx3.h"

Lexer InterpreterEx3::lexer;
Parser InterpreterEx3::parser;

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

InterpreterEx3::InterpreterEx3(vector<string> vecInterpret, int index) {
    this->vecInterpret = vecInterpret;
    this->index = index;
}

int InterpreterEx3::execute() {
    parser.execute();
}

Lexer& InterpreterEx3::getLexer() {
    return lexer;
}

Parser& InterpreterEx3::getParser() {
    return parser;
}
