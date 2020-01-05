//
// Created by sarah on 03/01/2020.
//

#include "DefineVarCommand.h"
/**
 * Constructor
 * this command creates variables with path to simulator and value
 * @param vect vector
 * @param index1 index in vector
 */
DefineVarCommand::DefineVarCommand(vector<string> vect, int index1) {
    this->vec = vect;
    this->index = index1;
}
/**
 * 3 cases:
 * 1. new vae definition - create a variable whith a path so simulation
 * 2. create a var whithout a path to simulation
 * 3. update a variable's value
 * @return next command index
 */
int DefineVarCommand::execute() {
//    var definition in fly.txt:
//    var name -> sin ("path")
//    var name <- sim ("path")
// i= 0    1   2   3     4
//    name = value
//i=   0   1  2

int reVal = index;
    //new var definition
    if (vec[index] == "var") {
        //add to map
        myTable->updateNameToPath(vec[index + 1], vec[index + 4]);
        reVal = index + 5;

        //if var is new and without a path, set in map
    } else if (myTable->nameToPath.count(vec[index]) == 0) {
        //check if it's an expression - simplyfy the expression
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
        //push to queue
        myTable->sendToServerQueue.push(name);
        reVal = index + 3;
    }
    return reVal;
}
/**
 * destructor
 */
DefineVarCommand::~DefineVarCommand(){}