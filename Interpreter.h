//
// Created by adi on 25/12/2019.
//

#ifndef STONEROAD1EX3_INTERPRETER_H
#define STONEROAD1EX3_INTERPRETER_H

#include "Parser.h"
#include "Lexer.h"
#include <ios>

class Interpreter {
//    Parser* parser;
//    virtual void ExecuteBySource(std::istream&) = 0;

//    static Lexer lexer;
    static Parser parser;

public:
//    Interpreter(Parser* parser);
//    void interperate(vector<string> &values);
//    void readLine(vector<string>::iterator &it);

    Interpreter();
    static void execute();
//    static Lexer& getLexer();
    static Parser& getParser();

    virtual ~Interpreter() = default;
};


#endif //STONEROAD1EX3_INTERPRETER_H
