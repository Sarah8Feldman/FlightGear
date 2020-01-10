//
// Created by sarah on 24/12/2019.
//
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <regex>
#include "Lexer.h"
/**
 * prints thre vector
 * @param vect vector
 */
void Lexer::print(vector<string> vect) {
    auto it = vect.begin();
    for (it; it != vect.end(); it++)
        std::cout << *it << ',';
}

/**
 * The expression With Out Spaces function deletes all white spaces from a string
 * @param str string
 * @return same string without spaces
 */
string Lexer::expressionWithOutSpaces(string str) {
    int i = 0;
    string stringWithOutSpace = "";
    while(i < str.size()){
        if(str[i] != ' '){
            stringWithOutSpace += str[i];
        }
        i++;
    }
    return stringWithOutSpace;
}
/**
 * return a vector of matches in a line
 * @param str string
 * @return string with spaces between 2 tokens
 */
vector<string> Lexer::regexMatches(string str) {

    string pattern = "(connectControlClient)\\((.+),(.+)\\)|(->)|(<-)|(\\})|(var)?\\s?([\\w]+)\\s?(=)\\s?(.+)\\n?|([\\w]+)\\((.+)\\)\\n?|(if|while)\\s([^<>=]+)\\s?([<=>]+)\\s?(.+)\\s?(\\{)\\n?|(var)\\s([\\w]+)|([\\w]+)\\s?(=)\\s?(.+)\\n?";

    auto matches = regexer(str, pattern);
    return matches;
}

/**
 * The regex function.
 * @param str our string
 * @param pattern for regex
 * @return matches - a vector with all matches
 */
vector<string> Lexer::regexer(string str, string pattern) {
    vector<string> matches;

    auto reg = regex(pattern);
    auto iter = sregex_iterator(str.begin(), str.end(), reg);
    auto ith = sregex_iterator();

    // loop the matches
    for (auto i = iter; i != ith; ++i) {
        int count = 0;
        for (string match : *i) {
            // skip empty matches
            if (match.empty()) {
                continue;
            }

            if (count > 0) {
                matches.push_back(match);
            }
            count++;
        }
    }

    return matches;
}

/**
 * Read a file - such as fly.txt
 * create a vector from this file
 * @param fileName name of file to read from
 * @return a vector of all commands and values from this file
 */
vector<string> Lexer::createVectorFromFile(string fileName) {
    vector<string> tmpVec;
    vector<string>::iterator it;
    vector<string> finalVec;
    //read from the file
    ifstream in_file;
    in_file.open(fileName, ios::in);
    if (!in_file) {
        throw ("an error");
    } else {
        string line;
        while (getline(in_file, line)) { //read data from file object and put it into string.
            tmpVec = regexMatches(line);
            for (it = tmpVec.begin(); it != tmpVec.end(); it++)
            {
                string token = *it;
                if (token[0] == ' ') {
                    token = token.substr(1);
                }

                if (token[token.length() - 1] == ' ') {
                    token.pop_back();
                }

                finalVec.push_back(token);
            }
        }
    }
    in_file.close(); //close the file object
    return finalVec;
}
/**
 * destructor
 */
Lexer::~Lexer(){}


