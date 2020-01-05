//
// Created by sarah on 03/01/2020.
//

#include "DefineVarCommand.h"
DefineVarCommand::DefineVarCommand(vector<string> vect, int index1) {
    this->vec = vect;
    this->index = index1;
//    this->myTable = table;
}
int DefineVarCommand::execute() {
//    var definition:
//    var name -> sin ("path")
//    var name <- sim ("path")
// i= 0    1   2   3     4
//    name = value
//i=   0   1  2

int reVal = index;
    //new var
    if (vec[index] == "var") {
        myTable->updateNameToPath(vec[index + 1], vec[index + 4]);
        reVal = index + 5;

        //if var is new, set in map
    } else if (myTable->nameToPath.count(vec[index]) == 0) {

        double value = ExpressionCommand::interpertExpression(vec[index + 2]);
        string sValue = to_string(value);
        myTable->updateVaresWithoutPath(vec[index],sValue);
        reVal = index + 3;

    }
    //if var already exist and we need to update the server
    else if ((myTable->nameToPath.count(vec[index]) > 0)){
        string name = vec[index];
        double value = stod(vec[index + 2]);
        myTable->pathsToValue[myTable->nameToPath[name]]= value;
        myTable->sendToServerQueue.push(name);
//        myTable->setValuetoServer(name, value);
        reVal = index + 3;
    }
    return reVal;
}
DefineVarCommand::~DefineVarCommand(){}