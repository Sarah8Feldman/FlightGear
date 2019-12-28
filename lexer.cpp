//
// Created by sarah on 24/12/2019.
//
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "lexer.h"

void Lexer::print(vector<string> vect) {
    auto it = vect.begin();
    for (it; it != vect.end(); it++)
        std::cout << *it << ';';
}

bool Lexer::isOperator(char op) {
    return (op == '=') || (op == '+') || (op == '-') || (op == '*') ||
           (op == '/') || (op == '%') || (op == '(') || (op == ')') ||
           (op == ',') || (op == '{') || (op == '}');
    }

bool Lexer::isEqualOp(char op1, char op2) {
    return (((op2 == '=') && (op1 == '=')) || (op1 == '!') || (op1 == '<') || (op1 == '>'));
}
bool Lexer::isArrow(char op1, char op2){
    return (((op1) == '-' && (op2 == '>')) || (op1 == '<') && (op2 == '-'));
}
//inserts a parser in the right spaces
string Lexer::insertParser (string str) {
    //push white space between spesific characters before we split to vector
    bool isQuotation = false;
    string stringWithOutSpace = "";
    string retStr = "";
    string mathExp = "";
    int counter = 0;
    int i =0;
    //delet all white spases from the string
    while(i < str.size()){
        if(str[i] != ' '){
            stringWithOutSpace += str[i];
        }
        i++;
    }

    i=0;
    while(i < str.size()) {
        if (stringWithOutSpace[i] == '\"') {
            //first Quotation mark -> true
            if (isQuotation == false) {
                isQuotation = true;
            }
            else {
                isQuotation = false;
            }
        }
        if(isArrow(stringWithOutSpace[i], stringWithOutSpace[i + 1])){
            retStr += stringWithOutSpace[i];
            retStr += stringWithOutSpace[i + 1];
            i+=2;
        }
        if(stringWithOutSpace[i] == '='){
            i++;
            while (i < stringWithOutSpace.size()){
                mathExp += stringWithOutSpace[i];
                i++;
            }
            retStr += parser + mathExp + parser;
        }

        if (!isQuotation && isEqualOp(stringWithOutSpace[i], stringWithOutSpace[i + 1])) {
            retStr += stringWithOutSpace[i];
            retStr += stringWithOutSpace[i + 1];
            i+=2;
        }
        if (isQuotation && isOperator(stringWithOutSpace[i])) {
            retStr += "\"" + parser + stringWithOutSpace[i] + parser + "\"";
        }
        if (stringWithOutSpace[i] == '('){
            while (stringWithOutSpace[i] != ','){
                if(stringWithOutSpace[i] == ' '){
                    i++;
                }
                if (stringWithOutSpace[i] == '('){
                    counter++;
                }
                if (stringWithOutSpace[i] == ')'){
                    counter--;
                }
                if(counter != 0){
                    mathExp +=stringWithOutSpace[i];
                    i++;
                }
                if(counter == 0){
                    mathExp +=stringWithOutSpace[i];
                    i++;
                    retStr += parser + mathExp + parser;
                    break;
                    mathExp = "";
                }
            }
        }

        if (!isQuotation && isOperator(stringWithOutSpace[i])) {
            retStr += parser + stringWithOutSpace[i] + parser;
        }

        else {
            if(stringWithOutSpace[i] != 0) {
                retStr += stringWithOutSpace[i];
            }
        }
        i++;
    }

    return retStr;
}
//create a vector from single string
vector<string> Lexer::splitStringToVector(string str) {
    vector<string> vectorWithSpaces;
    vector<string>::iterator it;
    vector<string> FinalVector;

    while(!str.empty())
    {
        int index = str.find(parser);
        //index is not in the end of string
        if (index != string::npos) {
            string pushStr = str.substr(0, index);
            vectorWithSpaces.push_back(pushStr);

            str = str.substr(index + parser.size());
            if (str.size() == 0)
            {
                vectorWithSpaces.push_back(str);
            }
        }
        else
        {
            vectorWithSpaces.push_back(str);
            str = "";
        }
    }
    //delete empty values in vector
    for (it = vectorWithSpaces.begin(); it != vectorWithSpaces.end(); it++)
    {
        if (*it != "") {
            if (*it != ",") {
                FinalVector.push_back(*it);
            }
        }
    }
    return FinalVector;
}
//create vector from a line
vector<string> Lexer:: createVectorFromLine(string str) {
    string  strWithParser = insertParser(str);
    vector<string> finalVector = splitStringToVector(strWithParser);
    print(finalVector);
    return finalVector;
}


vector<string> Lexer::createVectorFromFile(string fileName) {
    vector<string> tmpVec;
    vector<string>::iterator it;
    vector<string> finalVec;
    ifstream in_file;
    in_file.open(fileName, ios::in);
    if (!in_file) {
        throw ("an error");
    } else {
        string line;
        while (getline(in_file, line)) { //read data from file object and put it into string.
            tmpVec = createVectorFromLine(line);
            for (it = tmpVec.begin(); it != tmpVec.end(); it++)
            {
                finalVec.push_back(*it);
            }
        }
    }
    in_file.close(); //close the file object
    return finalVec;
}


