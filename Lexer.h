//
// Created by sarah on 24/12/2019.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H
#include <vector>
#include <string>
using namespace std;

/**
 * The Lexer class.
 */
class Lexer {
private:
    void print(vector<string> vect);

public:
    string expressionWithOutSpaces (string str);

    vector<string> createVectorFromFile(string fileName);

    virtual ~Lexer();

    vector<string> regexer(string str, string pattern);

    vector<string> regexMatches(string str);
};
#endif //LEXER_LEXER_H
