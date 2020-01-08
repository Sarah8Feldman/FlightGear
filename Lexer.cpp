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
 *
 * @param op operator
 * @return true is char is an operator
 */
bool Lexer::isOperator(char op) {
    return (op == '=') || (op == '+') || (op == '-') || (op == '*') ||
           (op == '/') || (op == '%') || (op == '(') || (op == ')') ||
           (op == ',') || (op == '{') || (op == '}');
    }
/**
 * checks if the 2 chars are an iperator that onclude = : such as => or ==
 * @param op1 char 1
 * @param op2 char 2
 * @return true if is an operator of this kind
 */
bool Lexer::isEqualOp(char op1, char op2) {
    return (((op2 == '=') && (op1 == '=')) || (op1 == '!') || (op1 == '<') || (op1 == '>'));
}
/**
 * arrows : <- or ->
 * @param op1 char 1
 * @param op2 char 2
 * @return true if is an arrow
 */
bool Lexer::isArrow(char op1, char op2){
    return (((op1) == '-' && (op2 == '>')) || (op1 == '<') && (op2 == '-'));
}
/**
 * delets all white spases from a string
 * @param str string
 * @return string whithout spaces
 */
string Lexer::expressionWithOutSpaces(std::__cxx11::string str) {
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
 * returnd a vector of matches in a line
 * @param str string
 * @return string with spaces between 2 tokens
 */
vector<string> Lexer::regexMatches(string str) {

    string pattern = "(connectControlClient)\\((.+),(.+)\\)|(->)|(<-)|(\\})|(var)?\\s?([\\w]+)\\s?(=)\\s?(.+)\\n?|([\\w]+)\\((.+)\\)\\n?|(if|while)\\s([^<>=]+)\\s?([<=>]+)\\s?(.+)\\s?(\\{)\\n?|(var)\\s([\\w]+)|([\\w]+)\\s?(=)\\s?(.+)\\n?";

    auto matches = regexer(str, pattern);
    return matches;
}

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

//**
// * create a vector from single string
// * @param str string
// * @return vector from a single string
// */
//vector<string> Lexer::splitStringToVector(string str) {
//    vector<string> vectorWithSpaces;
//    vector<string>::iterator it;
//    vector<string> FinalVector;
//
//    while(!str.empty())
//    {
//        int index = str.find(parser);
//        //index is not in the end of string
//        if (index != string::npos) {
//            string pushStr = str.substr(0, index);
//            vectorWithSpaces.push_back(pushStr);
//
//            str = str.substr(index + parser.size());
//            if (str.size() == 0)
//            {
//                vectorWithSpaces.push_back(str);
//            }
//        }
//        else
//        {
//            vectorWithSpaces.push_back(str);
//            str = "";
//        }
//    }
//    //delete empty values in vector
//    for (it = vectorWithSpaces.begin(); it != vectorWithSpaces.end(); it++)
//    {
//        if (*it != "") {
//            if (*it != ",") {
//                FinalVector.push_back(*it);
//            }
//        }
//    }
//    return FinalVector;
//}
//
///**
// * create vector from a line
// * @param str string
// * @return vector
// */
//vector<string> Lexer:: createVectorFromLine(string str) {
//    vector<string> vec = regexMatches(str);
//    vector<string> finalVector = splitStringToVector(strWithParser);
//    print(finalVector);
//    return finalVector;
//}

/**
 * read a file - such as fly.txt
 * create a vector from this file
 * @param fileName
 * @return
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
                finalVec.push_back(*it);
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


