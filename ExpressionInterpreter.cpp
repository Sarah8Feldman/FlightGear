
#include <stack>
#include <sstream>
#include <queue>
#include "ExpressionInterpreter.h"

//**************************************Class Value************************************************
Value::Value (double e): value(e) {
}

Value::~Value() {
}

double Value::getValue() {
    return value;
}

double Value::calculate() {
    return getValue();
}
//************************************Class variable**************************************************
Variable::Variable(string myName, double myValue) {

    this->name = myName;
    this->value= myValue;
}
double Variable::getValue() {
    return value;
}

double Variable::calculate() {
    return getValue();
}

Variable& Variable::operator++() {
    this->value++;
    return *this;
}

Variable& Variable::operator--() {
    this->value = value - 1;
    return *this;
}

Variable& Variable::operator++(int) {
    this->value++;
    return *this;
}

Variable& Variable::operator--(int) {
    this->value--;
    return *this;
}

Variable& Variable::operator-=(double var) {
    this->value-=var;
    return *this;
}

Variable& Variable::operator+=(double var) {
    this->value+=var;
    return *this;
}

Variable::~Variable() {
}

//***************************************************Class UnaryOperator****************************
UnaryOperator::UnaryOperator(Expression* ex) {
    this->exp = ex;
}
UnaryOperator::~UnaryOperator() {
}

//*****************************************************Class UPlus*****************************************
UPlus::UPlus(Expression *e):UnaryOperator(e) {
}

UPlus::~UPlus() {
}

double UPlus::calculate() {
    return exp->calculate();
}
//*****************************************************Class Uminus****************************************
UMinus::UMinus(Expression *e):UnaryOperator(e) {
}

UMinus::~UMinus() {
}

double UMinus::calculate() {
    return exp->calculate()*(-1);
}
//*****************************************************Class BinaryOperator**********************************
BinaryOperator::BinaryOperator(Expression* right, Expression* left) {
    this->rightEx=right;
    this->leftEx=left;
}

BinaryOperator::~BinaryOperator(){
}

//*********************************************************Class Plus******************************************
Plus::Plus(Expression *left, Expression *right):BinaryOperator(right, left) {
}

double Plus::calculate() {
    return (leftEx->calculate() + rightEx->calculate());
}
Plus::~Plus() {
}

//********************************************************Class Minus*******************************************
Minus::Minus(Expression *left, Expression *right):BinaryOperator(right, left) {
}

double Minus::calculate() {
    return (leftEx->calculate() - rightEx->calculate());
}

Minus::~Minus() {
}
//********************************************************Class Mul*******************************************
Mul::Mul(Expression *left, Expression *right):BinaryOperator(right, left) {
}

double Mul::calculate() {
    return (leftEx->calculate() * rightEx->calculate());
}

Mul::~Mul() {
}

//***********************************************************Class Div**************************************8
Div::Div(Expression *left, Expression *right):BinaryOperator(right, left) {
}

double Div::calculate() {
    if(rightEx->calculate() == 0){
        throw "division by zero";
    }
    return (leftEx->calculate() / rightEx->calculate());
}

Div::~Div() {
}

//***************************************************Part 2*******************
Interpreter::~Interpreter() {
}

void Interpreter::printMap(const map<string, double>& myMap, string mapName)
{
    cout <<"----------"<<mapName<<"--------"<<endl;
    for(auto it = myMap.cbegin(); it != myMap.cend(); ++it)
    {
        cout << it->first << "=" << it->second<<" ";
    }
    cout <<endl<<"----------------------"<<endl;
}

void Interpreter::printQueue(const queue<string>& myQueue, string queueName)
{
    //printing content of queue
    cout <<"------"<<queueName<<"-----------"<<endl;
    queue<string> q = myQueue;
    while (!q.empty()){
        cout<<" "<<q.front();
        q.pop();
    }
    cout <<endl<<"----------------------"<<endl;
}

void Interpreter::printStack(const stack<char>& myStack, string stackName)
{
    cout <<"------"<<stackName<<"------------"<<endl;
    stack<char> s = myStack;
    while( !s.empty() ) {
        cout << s.top() << " ";
        s.pop();
    }
    cout <<endl<<"----------------------"<<endl;
}

void Interpreter::printStack(const stack<string>& myStack, string stackName)
{
    cout <<"------"<<stackName<<"------------"<<endl;
    stack<string> s = myStack;
    while( !s.empty() ) {
        cout << s.top() << " ";
        s.pop();
    }
    cout <<endl<<"----------------------"<<endl;
}

bool Interpreter::isNumber(const string& varValue)
{
    if (varValue.size()<1){
        return false;
    }
    for (unsigned int i = 0; i<varValue.size();i++){
        char c = varValue[i];
        if (c == operMinus && varValue.size() == 1){
            return false;
        }
        if (!isdigit(c) && c != dot && c != operMinus){
            return false;
        }
    }
    return true;
}

bool Interpreter::isValidVarName(const string& varName)
{
    if (isNumber(varName)) {
        string s;
    }
    // validate the first char is not number
    if (varName.size()<1){
        return false;
    }
    if (isdigit(varName[0])){
        return false;
    }
    else {
        for (unsigned int i = 0; i<varName.size();i++){
            char c = varName[i];
            if (!isalnum(c) && c != underscore ){
                return false;
            }
        }
    }
    return true;
}

void Interpreter::setVariables(const string& variables) {

    stringstream ss, input(variables);
    string token;
    char delimiter = ';', eq = '=';
    while (getline(input, token, delimiter)) {
        if (token.size() < 1){
            continue;
        }
        size_t eqIndex = token.find(eq);
        if (eqIndex != std::string::npos){
            string varName = token.substr(0, eqIndex);
            string varValue = token.substr(eqIndex+1);
            if (isValidVarName(varName) && isNumber(varValue)){
//                if (varName.compare("rpm")== 0) {
//                    cout << "print variable " << varName << eq << varValue << endl;
//                }
                varMap[varName]=stod(varValue);
//                cout << varName << " = " << varValue << endl;
            }
            else{
                // incorrect variable setting - throw exception
//                cout<<"illegal variable assignment!: "<<token<<endl;
                throw "illegal variable assignment!";
            }
        }
        else {
            // = was not found - throw exception
//            cout<<"illegal variable assignment!: "<<token<<endl;
            throw "illegal variable assignment!";
        }
    }
//    printMap(varMap, "variable map");
}

bool Interpreter::isBinOperation (const char c){
    if (c ==  '+' || c == '-' || c == '*' || c == '/'){
        return true;
    }
    return false;
}

bool Interpreter::isUnarOperation (const char c){
    if (c ==  '+' || c == '-' ){
        return true;
    }
    return false;
}

bool Interpreter::isBrakets (const char c){
    if (c ==  '(' || c == ')'){
        return true;
    }
    return false;
}


/**
 * The expression With Out Spaces function deletes all white spaces from a string
 * @param str string
 * @return string without spaces
 */
string Interpreter::removeSpacesFromString(string str) {
    int i = 0;
    string resultStr = "";
    while(i < str.size()){
        if(str[i] != ' '){
            resultStr += str[i];
        }
        i++;
    }
    return resultStr;
}

Expression*Interpreter::interpret(const string inputExpr) {

    stringstream strstream;
    stack<char> operStack;
    queue<string> postfixQ;
    bool isDigit = true;
    Expression* e = nullptr;

    string result = "";
    string varValue = "";
    string sign = "";
    bool probableUnarOper = false;
//    int c = varMap.count(inputExpr);
//    double v = varMap[inputExpr];

    if (isNumber(inputExpr)){ // check if inputExpr is number
        e = new Value(stod(inputExpr));
    }
    else if (isValidVarName(inputExpr)) { // not number but valid var name
        auto it = varMap.find(inputExpr);
        if (it != varMap.end() && isValidVarName(inputExpr)) {
            e = new Value(varMap.at(inputExpr));
        }
    }

    if (!e) { // not number and not in map

        string inputExpr1 = removeSpacesFromString(inputExpr);

            if (varMap.count(inputExpr1) == 0) {
                //    cout << "<<<>>> Expression: " << inputExpr << endl;
                for (unsigned int i = 0; i < inputExpr1.size(); i++) {
                    char cc = inputExpr1[i];
                    char nc = inputExpr1[i + 1];
                    if ((isalpha(cc) || cc == underscore)) {
                        //            cout<<"Variable char: "<<cc<<endl;
                        result = result + cc;
                        probableUnarOper = false;
                        if (isBinOperation(nc) || nc == rightBr) {
                            // variable name. replace it by value if exists, else throw exception
                            if (varMap.count(result) > 0) {
                                //                    varValue = to_string(varMap.find(result)->second);
                                varValue = to_string(varMap.find(result)->second);
                                if (!sign.empty() ) {
                                    operStack.push(sign[0]);
                                    sign = "";
                                }
                                postfixQ.push(varValue);
                                result = "";
                            } else {
                                //                    cout << "variable without value: " << result << endl;
                                result = "";
                                throw "illegal math expression";
                            }
                        }
                        //            cout<<"Variable value: "<<varValue<<endl;
                        varValue = "";
                    } else if ((isdigit(cc) || cc == dot)) {
                        //            cout<<"Digit: "<<cc<<endl;
                        result = result + cc;
                        probableUnarOper = false;
                        if (isBinOperation(nc) || nc == rightBr || nc =='\0') {
                            // could be double or variable
                            if (!isNumber(result)) {
                                // variable name with number. replace it by value if exists, else throw exception
                                if (varMap.count(result)) {
                                    varValue = to_string(varMap.find(result)->second);
                                    postfixQ.push(varValue);
                                } else {
                                    result = "";
                                    throw "illegal math expression";
                                }
                            } else {
                                postfixQ.push(result.insert(0, sign));
                            }
                            result = "";
                            sign = "";
                        }
                        //            cout<<"Number: "<<varValue<<endl;
                        varValue = "";
                    } else if (isBinOperation(cc)) {
                        if (isBinOperation(nc) && !isUnarOperation(nc) ) {
                            throw "illegal math expression";
                        }else{
                            if (isUnarOperation(nc)){
                                probableUnarOper = true;
                            }
                        }
                        if (isUnarOperation(inputExpr1[0])){
                            if(inputExpr1[0] == operMinus){
                                cc = unarMinus;
                            } else{
                                cc = unarPlus;
                            }
                        }
                        else if (cc == operMinus && nc != leftBr) {
                            if (cc == operMinus && probableUnarOper){
                                cc = unarMinus;
                            } else {
                                sign = "-";
                            }
                        } else {
                            if ((cc == operMinus && nc == leftBr && probableUnarOper) ||
                                (cc == operMinus && nc == leftBr && operStack.empty() && postfixQ.empty())) {
                                cc = unarMinus;
                            }
                            if ((cc == operPlus && nc == leftBr && probableUnarOper) ||
                                (cc == operPlus && nc == leftBr && operStack.empty() && postfixQ.empty())) {
                                cc = unarPlus;
                            }
                            if (!operStack.empty()) {
                                char topOper = operStack.top();
                                int currOperPrior = operMap.find(cc)->second;
                                int topOperPrior = operMap.find(topOper)->second;
                                if (topOperPrior >= currOperPrior) {
                                    operStack.pop();
                                    string s;
                                    s.push_back(topOper);
                                    postfixQ.push(s);
                                }
                            }
                            operStack.push(cc);
                            probableUnarOper = false;
                        }
                        //            cout<<"Operation: "<<cc<<endl;
                    } else if (cc == leftBr) {
                        if (nc == '-' || nc == '+') {
                            probableUnarOper = true;
                        }
                        operStack.push(cc);
                        //            cout<<"Left P: "<<cc<<endl;
                    } else if (cc == rightBr) {
                        probableUnarOper = false;
                        if (!operStack.empty()) {
                            char topOper = operStack.top();
                            while (topOper != leftBr) {
                                operStack.pop();
                                string s;
                                s.push_back(topOper);
                                postfixQ.push(s);
                                if (!operStack.empty()) {
                                    topOper = operStack.top();
                                } else {
                                    throw "incorrect bracket number";
                                }
                            }
                        }
                        operStack.pop();
                        //            cout<<"Right P: "<<cc<<endl;
                    }
                }

                while (!operStack.empty()) {
                    char topOper = operStack.top();
                    string s;
                    s.push_back(topOper);
                    postfixQ.push(s);
                    operStack.pop();
                }
                //    printQueue(postfixQ, "postfix queue");
                //    printStack(operStack, "operations stack");
//                cout<<"Expr: "<<inputExpr<<endl;
                e = evalPostfix(postfixQ);
            }
        }


//    printMap(varMap, "varMap");
    return e;
}


Expression* Interpreter::createExpressionValue(Expression* op1, Expression* op2, char operate){
    switch (operate) {
        case '*': return new Mul(op1,op2);
        case '/': return new Div(op1, op2);
        case '+': return new Plus(op1,op2);
        case '-': return new Minus(op1,op2);
        case '!': return new UPlus(op2);
        case '~': return new UMinus(op2);
        default : return 0;
    }
}



Expression* Interpreter::evalPostfix(const queue<string> postfix ) {
//posfix to infix algorithem - using 2 stacks
    stack<Expression*> expressionStack;
    queue<string> q = postfix;
    while (!q.empty()){
        string element = q.front();
        if (isNumber(element)){
            Expression* e = new Value(stod(element));
            expressionStack.push(e);
        } else {
            char oper = element[0];
            Expression *e1 = expressionStack.top();
            expressionStack.pop();
            Expression *e2;
            if (isBinOperation(oper)) {
                e2 = expressionStack.top();
                expressionStack.pop();
            } else {
                e2 = nullptr;
            }
            Expression* resultExpression = createExpressionValue(e2,e1,oper);
            expressionStack.push(resultExpression);
        }
        q.pop();
    }
    return expressionStack.top();
}