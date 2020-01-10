//
// Created by sarah on 03/01/2020.
//

#include "DefineVarCommand.h"
#include "ExpressionInterpreter.h"

/**
 * Constructor
 * this command creates variables with path to simulator and value
 * @param vect vector from lexer
 */
DefineVarCommand::DefineVarCommand(vector<string> vecDefine) {
    this->vecDefine = vecDefine;
    globalMaps = SymbolTable::getInstance();
}
/**
 * The execute function have 3 cases:
 * 1. new vae definition - create a variable whith a path so simulation
 * 2. create a var whithout a path to simulation
 * 3. update a variable's value
 * @param index of command in the lexer vector
 * @return next command index
 */
int DefineVarCommand::execute(int index) {
//    var definition in fly.txt:
//    var name -> sin ("path")
//    var name <- sim ("path")
// i= 0    1   2   3     4
//    name = value
//i=   0   1  2
//    var name = value
//i =  0    1  2   3

    int reVal = index;

    //new var definition
    if (vecDefine[index] == "var") {
        //var definition with a path
        if(vecDefine[index + 2] != "=") { // it has an arrow -> or <-
            //add to map
            string path = vecDefine[index + 4];
            path  = path.substr(1);
            path.pop_back();
            //update the name to path map
            globalMaps->updateNameToPath(vecDefine[index + 1], path);

            //update the varMap in the expression interpreter
            updateMapForExpressionInterpreter(vecDefine[index + 1],to_string(globalMaps->pathsToValueMap.at(path)));

            //update the map path to arrow diraction so we'll know wich variables we update to the simulation "->",
            //and which we get updated by the simulation "<-"
            globalMaps -> pathToArrowDir[path] = vecDefine[index + 2];

            //return the index of the nex command
            reVal = index + 5;

        } else { //var definition without a path
            //calculate the calue in case it is an expression
            double value = ExpressionCommand::interpertExpression(vecDefine[index + 3]);
            string sValue = to_string(value);

            //update the values without path map
            globalMaps->updateVaresWithoutPath(vecDefine[index + 1], sValue);

            //update the map in expression iterpreter
            updateMapForExpressionInterpreter(vecDefine[index + 1],sValue);

            //return the index of the nex command
            reVal = index + 4;
        }

        //if var already exist in our varsWithoutPathMap map we only need to update our data
    } else if (globalMaps->varsWithoutPathMap.count(vecDefine[index]) > 0) {
        //calculate the value in case it is an expression
        double value = ExpressionCommand::interpertExpression(vecDefine[index + 2]);
        string sValue = to_string(value);

        //update the values without path map
        globalMaps->updateVaresWithoutPath(vecDefine[index], sValue);

        //update the map in expression iterpreter
        updateMapForExpressionInterpreter(vecDefine[index],sValue);

        //return the index of the nex command
        reVal = index + 3;

    }
    //if var already exist and we need to update the simulation -
    else if ((globalMaps->nameToPathMap.count(vecDefine[index]) > 0)){
        string name = vecDefine[index];
        //calculate the value in case it is an expression
        double value = ExpressionCommand::interpertExpression(vecDefine[index + 2]);
        //update the value in path to value map
        globalMaps->pathsToValueMap[globalMaps->nameToPathMap[name]]= value;

        //push to the commands for client queue
        globalMaps->clientCommandsQueue.push(name);

        //update the map in expression iterpreter
        updateMapForExpressionInterpreter(name,vecDefine[index + 2]);

        //return the index of the nex command
        reVal = index + 3;
    }
    return reVal;
}
/**
 * destructor
 */
DefineVarCommand::~DefineVarCommand(){}

/**
 * update the "varMap" map in expresion interpreter
 * @param name of variable
 * @param value of variable
 */
void DefineVarCommand::updateMapForExpressionInterpreter(string name, string value) {
     //calculate the value in case it is an expression
    string resValue = to_string(ExpressionCommand::interpertExpression(value));

    //create a string of the variable initialization -> "name=value;"
    string command = name+ "=" + resValue + ";";

    //set the variable to the expression interpreter
    globalMaps->interpreter.setVariables(command);
}