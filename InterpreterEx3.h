//
// Created by adi on 25/12/2019.
//

#ifndef STONEROAD1EX3_INTERPRETEREX3_H
#define STONEROAD1EX3_INTERPRETEREX3_H

#include "Parser.h"
#include "Lexer.h"
#include <ios>

class InterpreterEx3 {
private:
//    Parser* parser;
//    virtual void ExecuteBySource(std::istream&) = 0;
    vector<string> vecInterpret;
    int index;
    static Lexer lexer;
    static Parser parser;

public:
//    Interpreter(Parser* parser);
//    void interperate(vector<string> &values);
//    void readLine(vector<string>::iterator &it);

    InterpreterEx3(vector<string> vecInterpret, int index);

    int execute();
    static Lexer& getLexer();
    static Parser& getParser();

    virtual ~Interpreter() = default;
};


#endif //STONEROAD1EX3_INTERPRETEREX3_H
