//
// Created by adi on 03/01/2020.
//

#include "OpenServerCommand.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <regex>

/**
 * The Open Server Command gets data from the server about flight variables and updates them to our map
 * @param vecOpenServer vector
 */
OpenServerCommand::OpenServerCommand(vector<string> vecOpenServer) {
    this->vecOpenServer = vecOpenServer;
    globalMaps = SymbolTable::getInstance();
}

/**
 * This function update the paths to values map.
 * @param values vector of values
 */
void OpenServerCommand::updateMaps(vector<double> values){
    globalMaps->gMutex.lock();
    //we iterate over the map and update only that have "<-"
    //all 36 values are set on the same indexs
    auto it = globalMaps -> pathsToValueMap.begin();
    for (int i = 1; i <= 36; ++i) {
        string path = globalMaps -> indexToPath[i];
        if (globalMaps -> pathToArrowDir[path] == "<-") {
            globalMaps -> pathsToValueMap[path] = values[i - 1];
        }
    }

//update varMap in the expression interpreter
    updateMapForExpressionInterpreter();

    globalMaps->gMutex.unlock();
}

/**
 * Update the "varMap" in the Expression Interpreter.
 */
void OpenServerCommand::updateMapForExpressionInterpreter() {

    auto it = globalMaps->nameToPathMap.begin();
    auto fit = globalMaps->nameToPathMap.end();
    int i = 0;
    //set all of the variables from simulator so that the interpreter can use them as variables
    for (it; it != globalMaps->nameToPathMap.end(); it++) {
        string var_name = it->first;
        string var_value = to_string(globalMaps->pathsToValueMap.at(it->second));
        //check if the variable name isn't a number
        if (!isdigit(var_name[0])){
            //create a string of the variable initialization -> "name=value;"
            globalMaps->interpreter.setVariables(var_name + "=" + var_value + ";");
        }
    }
}

/**
 * Runs the thread.
 * @param client_socket
 */
void OpenServerCommand::runThread(int client_socket){
    //in this thread we get 36 values of the flight variables and we update our data accordingly
    //we create a vector of 36 values.
    //the values are red from the buffer - \n...values...\n, and then update uur maps

    char buffer[1024] = {0};
    ssize_t lineVals = read(client_socket, buffer, sizeof(buffer));
    string line = "";

    //reading from client
    while (buffer[0] != '\n') {
        int commas = 0;
        int index = 0;

        while (buffer[index] != '\n') {
            line += buffer[index++];

            if (buffer[index] == ',') {
                commas++;
            }
        }

        //updating the map with the received data
        if (commas == 35) {
            vector<double> vec = stringToDoubleVector(line);
            updateMaps(vec);
        }
        line ="";

        //read again
        read(client_socket, buffer, 1024);
    }
}

/**
 * The execute function.
 * @param index in the lexer vector of this command
 * @return the index of the next command
 */
int OpenServerCommand::execute(int index) {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    cout << "Open the server socket on " <<"0.0.0.0:"<<stoi(vecOpenServer[index+1]) <<endl;
    address.sin_port = htons(stoi(vecOpenServer[index+1]));

    //we need to convert our number
    // to a number that the network understands.
    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr<<"Error during listening command"<<std::endl;
        return -3;
    } else{
        std::cout<<"Server is now listening ..."<<std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);
    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }

    //celling to thread
    //this_thread::sleep_for(chrono::seconds(10));
    thread threadOSC([=]{runThread(client_socket);});
    threadOSC.detach();
    close(socketfd); //closing the listening socket


//        in fly.txt:
//    openDataServer(5400)
// index   0          1
//we return the next command index
    return index + 2;
}

/**
 * destructor
 */
OpenServerCommand::~OpenServerCommand(){}

/**
 * create a vector<double> from a string, the delimiter is ",".
 * @param str string
 * @return vector of doubles
 */
vector<double> OpenServerCommand::stringToDoubleVector(string str){
    globalMaps -> gMutex.lock();
    string num = "";
    vector<double> vec;

    stringstream ss(str);
    string s;
    while (getline(ss, s, ',')) {
        vec.push_back(stod(s));
    }

    globalMaps -> gMutex.unlock();
    return vec;
}
