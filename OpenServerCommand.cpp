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
/**
 * this command gets data from the server about flight variables and updates them to our map
 * @param vecOpenServer vector
 * @param index in vector
 */
OpenServerCommand::OpenServerCommand(vector<string> vecOpenServer, int index) {
    this->vecOpenServer = vecOpenServer;
    this->index = index;
    string iP = vecOpenServer[index + 1];
    int port = index + 2;
}
/**
 *
 * @return the index of the next command
 */
int OpenServerCommand::execute() {
    //create a separate thread for reading values from the simulator
    myTable->serverThread = thread(&OpenServerCommand::runThread, this);

//        in fly.txt:
//    openDataServer(5400)
// index   0          1
    return index + 2;
}
/**
 * Runs the thread
 */
void OpenServerCommand::runThread(){
    //create socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    //bind socket to IP address. creating a socket address object.
    sockaddr_in address;
    address.sin_family = AF_INET; //IP4
    address.sin_addr.s_addr = INADDR_ANY;//localhost
    address.sin_port = htons(index + 2);

    if (bind(serverSocket, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }

//    //making socket listen to the port
//    if(listen(serverSocket, 5) == -1) {
//        std::cerr<<"Error during listening command"<<std::endl;
//    }

    int client_socket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t*)&address);
//  if fail to connect - try again
    while (serverSocket == -1) {
        serverSocket = accept(serverSocket, (struct sockaddr *)&address, (socklen_t*)&address);
    }

    //reading from client
    char buffer[1024] = {0};
    read(client_socket, buffer, 1024);
    //create a string
    string str = bufferToString(buffer);
    //create a vector from the string
    vector<string> vec = stringToVector(str);
    //update map with new flight values
    myTable->updatePathValue(vec);

    close(serverSocket);
}
/**
 * create a string between every '\n' from the csv(buffer)
 * @param buff buffer
 * @return a new string - a line from the csv
 */
string OpenServerCommand::bufferToString(char *buff){
    int i = 0;
    string str = "";
    if(buff[0] == '\n'){
        i++;
    }
    while (buff[i] != '\n'){
        str.push_back(buff[i]);
        i++;
    }
    return str;
}
/**
 * create a vector from the string
 * the delimiter is ','
 * @param str string
 * @return vector
 */
vector<string> OpenServerCommand::stringToVector(string str){
    string parser = ",";
    int index = str.find(parser);
    vector<string> vect;
    //index is not in the end of string
    if (index != string::npos) {
        string pushStr = str.substr(0, index);
        vect.push_back(pushStr);
        str = str.substr(index + parser.size());
        if (str.size() == 0) {
            vect.push_back(str);
        }
    } else {
        vect.push_back(str);
        str = "";
    }
}/**
 * destructor
 */
OpenServerCommand::~OpenServerCommand(){}


