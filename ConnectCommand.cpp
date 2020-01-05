//
// Created by adi on 24/12/2019.
//

#include "ConnectCommand.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>


/**
 * ConnectCommand is a command in which we send and update values to the simulator
 * @param vecConnect vector from lexer
 * @param index in vector
 */
ConnectCommand::ConnectCommand(vector<string> vecConnect, int index) {
    this->vecConnect = vecConnect;
    this->index = index;
    string iP = vecConnect[index + 1];
    int port = index + 2;
    this->sim = sim;
}
/**
 *
 * @return the index of the next command
 */
int ConnectCommand::execute() {
    //create a separate thread for sending values to simulator
    myTable->clientTread = thread(&ConnectCommand::runThread, this);
//    in fly.txt:
//    connectControlClient("127.0.0.1",5402)
// index   0                   1         2
    return index + 3;
}
/**
 * Runs the thread
 */
void ConnectCommand::runThread(){
    //create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    //create a socket address object to hold address of server
    sockaddr_in address;
    address.sin_family = AF_INET; //IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//localhost
    address.sin_port = htons(index + 2);
//  when not able to connect - try again
    while (clientSocket == -1) {
        clientSocket = connect(clientSocket, (struct sockaddr *)&address, sizeof(address));
    }

    //Requesting a connection with the server on local host with port.
    int is_connect = connect(clientSocket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
    //all names variable for updating the simulator are in a queue
    string name = myTable->sendToServerQueue.front();
    //the values of the variables are in the maps
    double value = myTable->pathsToValue[myTable->nameToPath[name]];
    //write to the server
    char writeToServer[500] = "set ";
    strcat(writeToServer, myTable->nameToPath.at(name).c_str());
    strcat(writeToServer, " ");
    strcat(writeToServer, to_string(value).c_str());
    strcat(writeToServer, "\r\n");
    int n = write(clientSocket, writeToServer, strlen(writeToServer));
    if (n < 0) {
        throw "Error writing to socket";
        }
    myTable->sendToServerQueue.pop();
    close(clientSocket);
    }
/**
 * destructor
 */
ConnectCommand::~ConnectCommand() {}
