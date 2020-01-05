//
// Created by sarah on 24/12/2019.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H
#include <vector>
#include <string>
using namespace std;

class Lexer {
private:
    void print(vector<string> vect);
public:
    const string parser = " ";
    string insertParser (string stringWithOutSpace);
    bool isOperator(char op);
    bool isEqualOp(char op1, char op2);
    bool isArrow(char op1, char op2);
    string expressionWithOutSpaces (string str);
    vector<string> splitStringToVector(string str);
    vector<string> createVectorFromLine(string str);
    vector<string> createVectorFromFile(string fileName);
    virtual ~Lexer();



};
#endif //LEXER_LEXER_H
