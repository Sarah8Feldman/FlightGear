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

OpenServerCommand::OpenServerCommand(vector<string> vecOpenServer, int index, string sim) {
    this->vecOpenServer = vecOpenServer;
    this->index = index;
    string iP = vecOpenServer[index + 1];
    int port = index + 2;
    this->sim = sim;
}

int OpenServerCommand::execute() {
    //create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

//    if (serverSocket == -1) {
//        //error
//        std::cerr << "Could not create a socket"<<std::endl;
//        return -1;
//    }

    //bind socket to IP address. creating a socket address object.
    sockaddr_in address;
    address.sin_family = AF_INET; //IP4
    address.sin_addr.s_addr = INADDR_ANY;//localhost
    address.sin_port = htons(index + 2);

    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::cerr<<"Could not bind the socket to an IP"<<std::endl;
        return -2;
    }

    //making socket listen to the port
    if(listen(serverSocket, 5) == -1) {
        std::cerr<<"Error during listening command"<<std::endl;
        return -3;
    }

    int client_socket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t*)&address);

    while (serverSocket == -1) {
        serverSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t*)&address);
    }

    if (client_socket == -1) {
        std::cerr<<"Error accepting client"<<std::endl;
        return -4;
    }

    close(serverSocket);
    //reading from client
    char buffer[1024] = {0};
    int valueRead = read(client_socket, buffer, 1024);
    std::cout<<buffer<<std::endl;

    //string to char
    std::string str = "string";
    char *sim = new char[str.length() + 1];
    strcpy(sim, str.c_str());

    //writing back to client
    send(client_socket, sim, strlen(sim), 0);
    std::cout<<"Hello message sent\n"<<std::endl;
    return 0;

}

