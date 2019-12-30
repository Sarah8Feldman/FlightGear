//
// Created by adi on 24/12/2019.
//

#ifndef STONEROAD1EX3_PARSER_H
#define STONEROAD1EX3_PARSER_H

#include "Command.h"
//#include "Lexer.h"
#include <string>
#include <vector>
#include <map>
#include <iterator>
#include <list>

class Parser {
//    Parser* parser;
//    vector<string> condition;
//    vector<string> backupCondition;
//    vector<string> InsideTheBrackets;

    static map<string,Command*> commandMap;
    Command* getCommandFromString(string string1);

public:
//    Parser(Parser* newParser);
//    virtual void execute(vector<string>::iterator &it);

    Parser();
    static void execute();
    void parser(list<string> elements);
    virtual ~Parser();
};


#endif //STONEROAD1EX3_PARSER_H
