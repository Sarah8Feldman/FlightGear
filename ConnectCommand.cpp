//
// Created by adi on 24/12/2019.
//

#include "ConnectCommand.h"
#include "SymbolTable.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>


/**
 * ConnectCommand class is a command in which we send and update values to the simulator.
 * We act as a client who sends requests to the simulator.
 * @param vecConnect vector from lexer

 */
ConnectCommand::ConnectCommand(vector<string> vecConnect) {
    this->vecConnect = vecConnect;
    globalMaps = SymbolTable::getInstance();

}

/**
 * Runs the thread.
 * @param clientSocket the socket we opend
 * @return void function
 */
void ConnectCommand::runThread(int clientSocket){
        globalMaps->gMutex.lock();
        while (!globalMaps->clientCommandsQueue.empty()) {

            //all names variable for updating the simulator are in a queue
            string name = globalMaps->clientCommandsQueue.front();

            //the values of the variables are in the maps
            double value = globalMaps->pathsToValueMap[globalMaps->nameToPathMap[name]];
            //we send a set command to the simulator - "set this/is/the/path value"
            char writeToClientBuffer[500] = "set ";
            strcat(writeToClientBuffer, globalMaps->nameToPathMap.at(name).c_str());
            strcat(writeToClientBuffer, " ");
            strcat(writeToClientBuffer, to_string(value).c_str());
            strcat(writeToClientBuffer, "\r\n");
            //cout << ">>>Write to sim command " << writeToClientBuffer << endl;
            int n = write(clientSocket, writeToClientBuffer, strlen(writeToClientBuffer));
            if (n < 0) {
                throw "Error writing to socket";
            }
            globalMaps->clientCommandsQueue.pop();
        }
        globalMaps->gMutex.unlock();

    close(clientSocket);
}



/**
 * The execute function.
 * @param index
 * @return the index of the next command
 */
int ConnectCommand::execute(int index) {
    iP = vecConnect[index + 1];
    port = vecConnect[index + 2];





    //create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    //create a socket address object to hold address of server
    sockaddr_in address;
    address.sin_family = AF_INET; //IP4
    char ip[100];
    strcpy(ip, iP.c_str());
    address.sin_addr.s_addr = inet_addr(ip);//localhost
    address.sin_port = htons(stoi(port));
//  when not able to connect - try again
    if (clientSocket == -1) {
        cerr << "Can't connect to simulator" << endl;
    }

    //Requesting a connection with the server on local host with port.
    int is_connect = connect(clientSocket, (struct sockaddr *)&address, sizeof(address));
//    while (is_connect == -1) {
//        is_connect = connect(clientSocket, (struct sockaddr *)&address, sizeof(address));
//    }

//    this_thread::sleep_for(chrono::seconds(10));
    thread threadCC([=]{ runThread(clientSocket);});
    threadCC.detach();





    //create a separate thread for sending values to simulator
//    globalMaps->clientTread = thread(&ConnectCommand::runThread, this);
//    in fly.txt:
//    connectControlClient("127.0.0.1",5402)
// index   0                   1         2
    return index + 3;
}






/**
 * destructor
 */
ConnectCommand::~ConnectCommand() {}