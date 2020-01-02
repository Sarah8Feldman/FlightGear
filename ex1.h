//
// Created by sarah on 11/11/2019.
//

#ifndef EX1_EX1_EX1_H_
#define EX1_EX1_EX1_H_

#include <string>
#include <map>
#include <stack>
#include <queue>
#include "Expression.h"
#include "iostream"

using namespace std;

class Value : public Expression {
private:
    const double value;
public:
    Value(double e);
    double getValue();
    virtual ~Value();
    double calculate();


};

class Variable : public Expression {
private:
    double value;
    string name;

public:
    Variable(string name, double value);
    double getValue();
    Variable& operator++();
    Variable& operator--() ;
    Variable& operator+=(double var) ;
    Variable& operator-=(double var) ;
    Variable& operator++(int) ;
    Variable& operator--(int) ;
    double calculate();
    virtual ~Variable();
};

class UnaryOperator : public Expression {
protected:
    Expression* exp;
public:
    UnaryOperator(Expression* ex);
    virtual ~UnaryOperator();
};

class UPlus : public UnaryOperator {
public:
    UPlus(Expression* ex);
    virtual ~UPlus();
    double calculate();
};

class UMinus : public UnaryOperator {
public:
    UMinus(Expression* ex);
    virtual ~UMinus();
    double calculate();
};

class BinaryOperator : public Expression {
protected:
    Expression* rightEx;
    Expression* leftEx;
public:
    BinaryOperator(Expression* right, Expression* left);
    virtual ~BinaryOperator();
};

class Plus : public BinaryOperator {
public:
    Plus(Expression* right, Expression* left);
    double calculate();
    virtual ~Plus();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression* right, Expression* left);
    double calculate();
    virtual ~Minus();
};

class Mul : public BinaryOperator {
public:
    Mul(Expression* right, Expression* left);
    double calculate();

    virtual ~Mul();
};

class Div : public BinaryOperator {
public:
    Div(Expression* right, Expression* left);
    double calculate();
    virtual ~Div();
};

class Interpreter {
private:
    map<char, int> operMap = {
            {'+',1},
            {'-',1},
            {'*',2},
            {'/',2},
            {'!',3},
            {'~',3}
    };
    const char operPlus = '+';
    const char operMinus = '-';
    const char operDiv = '/';
    const char operMul = '*';
    const char leftBr = '(';
    const char rightBr = ')';
    const char unarPlus = '!';
    const char unarMinus = '~';
    const char firstChar = '|';
    const char dot = '.';
    const char underscore = '_';
    const char comma = ',';

    map<string, double > varMap;
    bool isNumber(const string& s);
    bool isValidVarName(const string& s);
    void printMap(const map<string, double>& map, string mapName);
    void printQueue(const queue<string>& myQueue, string queueName);
    void printStack(const stack<char>& myStack, string stackName);
    void printStack(const stack<string>& myStack, string stackName);
    bool isBinOperation (const char c);
    bool isBrakets (const char c);
    Expression* createExpressionValue(Expression* op1, Expression* op2, char operate);
    Expression* evalPostfix(const queue<string> postfix);

public:
    void setVariables(const string& variables);
    Expression* interpret(string infix);
    virtual  ~Interpreter();
};


#endif //EX1_EX1_EX1_H_