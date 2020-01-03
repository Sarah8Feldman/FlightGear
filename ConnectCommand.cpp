//
// Created by adi on 24/12/2019.
//

//#include <bits/socket_type.h>
//#include <bits/socket.h>
#include "ConnectCommand.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <cstring>
#include <string.h>
#include <unistd.h>

#define PORT 8081

in_addr_t inet_addr();

ConnectCommand::ConnectCommand(vector<string> vecCommand, int index, string sim) {
    this->vecCommand = vecCommand;
    this->index = index;
    string iP = vecCommand[index + 1];
    int port = index + 2;
    this->sim = sim;
}

int ConnectCommand::execute() {
    //create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        return -1;
    }
    //create a socket address object to hold address of server
    sockaddr_in address;
    address.sin_family = AF_INET; //IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//localhost
    address.sin_port = htons(index + 2);

    //Requesting a connection with the server on local host with port.
    int is_connect = connect(clientSocket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
        return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
    //string to char
    std::string str = "string";
    char *sim = new char[str.length() + 1];
    strcpy(sim, str.c_str());

    //if they were able to connection
    int is_sent = send(clientSocket, sim, strlen(sim), 0);
    if (is_sent == -1) {
        std::cout<<"Error sending message"<<std::endl;
    } else {
        std::cout<<"Hello message sent to server" <<std::endl;
    }

    char buffer[1024] = {0};
    int valueRead = read(clientSocket, buffer, 1024);
    std::cout<<buffer<<std::endl;

    close(clientSocket);
    return 0;
}

ConnectCommand::~ConnectCommand() {}
