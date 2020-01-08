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
 * this command gets data from the server about flight variables and updates them to our map
 * @param vecOpenServer vector
 * @param index in vector
 */
OpenServerCommand::OpenServerCommand(vector<string> vecOpenServer) {
    this->vecOpenServer = vecOpenServer;

}

void OpenServerCommand::updateMap(vector<double> values){

    myMutex.lock();
myTable->pathsToValue.at("/instrumentation/airspeed-indicator/indicated-speed-kt") = values [0];
myTable->pathsToValue.at("/sim/time/warp") = values [1];
myTable->pathsToValue.at("/controls/switches/magnetos") = values [2];
myTable->pathsToValue.at("/instrumentation/heading-indicator/offset-deg") = values [3];
myTable->pathsToValue.at("/instrumentation/altimeter/indicated-altitude-ft") = values [4];
myTable->pathsToValue.at("/instrumentation/altimeter/pressure-alt-ft") = values [5];
myTable->pathsToValue.at("/instrumentation/attitude-indicator/indicated-pitch-deg") = values [6];
myTable->pathsToValue.at("/instrumentation/attitude-indicator/indicated-roll-deg") = values [7];
myTable->pathsToValue.at("/instrumentation/attitude-indicator/internal-pitch-deg") = values [8];
myTable->pathsToValue.at("/instrumentation/attitude-indicator/internal-roll-deg") = values [9];
myTable->pathsToValue.at("/instrumentation/encoder/indicated-altitude-ft") = values [10];
myTable->pathsToValue.at("/instrumentation/encoder/pressure-alt-ft") = values [11];
myTable->pathsToValue.at("/instrumentation/gps/indicated-altitude-ft") = values [12];
myTable->pathsToValue.at("/instrumentation/gps/indicated-ground-speed-kt") = values [13];
myTable->pathsToValue.at("/instrumentation/gps/indicated-vertical-speed") = values [14];
myTable->pathsToValue.at("/instrumentation/heading-indicator/indicated-heading-deg") = values [15];
myTable->pathsToValue.at("/instrumentation/magnetic-compass/indicated-heading-deg") = values [16];
myTable->pathsToValue.at("/instrumentation/slip-skid-ball/indicated-slip-skid") = values [17];
myTable->pathsToValue.at("/instrumentation/turn-indicator/indicated-turn-rate") = values [18];
myTable->pathsToValue.at("/instrumentation/vertical-speed-indicator/indicated-speed-fpm") = values [19];
myTable->pathsToValue.at("/controls/flight/aileron") = values [20];
myTable->pathsToValue.at("/controls/flight/elevator") = values [21];
myTable->pathsToValue.at("/controls/flight/rudder") = values [22];
myTable->pathsToValue.at("/controls/flight/flaps") = values [23];
myTable->pathsToValue.at("/controls/engines/engine/throttle") = values [24];
myTable->pathsToValue.at("/controls/engines/current-engine/throttle") = values [25];
myTable->pathsToValue.at("/controls/switches/master-avionics") = values [26];
myTable->pathsToValue.at("/controls/switches/starter") = values [27];
myTable->pathsToValue.at("/engines/active-engine/auto-start") = values [28];
myTable->pathsToValue.at("/controls/flight/speedbrake") = values [29];
myTable->pathsToValue.at("/sim/model/c172p/brake-parking") = values [30];
myTable->pathsToValue.at("/controls/engines/engine/primer") = values [31];
myTable->pathsToValue.at("/controls/engines/current-engine/mixture") = values [32];
myTable->pathsToValue.at("/controls/switches/master-bat") = values [33];
myTable->pathsToValue.at("/controls/switches/master-alt") = values [34];
myTable->pathsToValue.at("/engines/engine/rpm") = values [35];
myMutex.unlock();
}

/**
 * Runs the thread
 */
void OpenServerCommand::runThread(int client_socket){

        //reading from client
        char buffer[1024] = {0};
        while (read(client_socket, buffer, 1024) != -1) {
            string str = bufferToString(buffer);
            vector<double> vec = stringToDoubleVector(str);
//            cout << "vector size is " << vec.size() << endl;
            if (vec.size() == 36) {
                updateMap(vec);
            }
        }

    close(client_socket);

}

/**
 *
 * @return the index of the next command
 */
int OpenServerCommand::execute(int index) {
//    port = vecOpenServer[index + 1];
//    //create socket
//    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
//
//    if(socketfd == -1) {
//        cerr<<"Could not create a socket"<<endl;
//        return -1;
//    }
//
//    //bind socket to IP address. creating a socket address object.
//    sockaddr_in address;
//    address.sin_family = AF_INET; //IP4
//    address.sin_addr.s_addr = INADDR_ANY;//localhost
//    port = port;
//    int portint = stoi(port);
//    address.sin_port = htons(portint);
//
//    if (bind(socketfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
//        cerr << address.sin_addr.s_addr << endl;
//        cerr << address.sin_port << endl;
//        std::cerr << "Could not bind the socket to an IP" << std::endl;
//        return -2;
//    }
//
//    //making socket listen to the port
//    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
//        std::cerr<<"Error during listening command"<<std::endl;
//        return -3;
//    } else{
//        std::cout<<"Server is now listening..."<<std::endl;
//    }
//
//    int client_socket = accept(socketfd, (struct sockaddr *)&address, (socklen_t*)&address);
////  if fail to connect - try again
//    if (client_socket == -1) {
//        std::cerr<<"Error accepting client"<<std::endl;
//        return -4;
//    } else {
//        cout << "Simulator connected to server" << endl;
//    }
////    if(client_socket!= -1){
////        myTable -> serverIsUp = true;
////    }
//    close(socketfd);



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
    cout <<stoi(vecOpenServer[index+1]) <<endl;
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

    close(socketfd); //closing the listening socket

    //celling to thread
    this_thread::sleep_for(chrono::seconds(10));
    //thread threadOSC([=]{serverThread(client_socket);});
    thread threadOSC([=]{runThread(client_socket);});
    //threadOSC.join();
    //this_thread::sleep_for(chrono::seconds(200000));
    threadOSC.detach();


//        in fly.txt:
//    openDataServer(5400)
// index   0          1
    return index + 2;
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
//    cout<< "printing buffer" << endl;
//    cout<< str << endl;
    return str;
}
/**
 * create a vector from the string
 * the delimiter is ','
 * @param str string
 * @return vector
 */
vector<double> OpenServerCommand::stringToVector(string str){
    string parser = ",";
    int index = str.find(parser);
    vector<double> vect;
    //index is not in the end of string
    if (index != string::npos) {
        string pushStr = str.substr(0, index);
        vect.push_back(stod(pushStr));
        str = str.substr(index + parser.size());
        if (str.size() == 0) {
            vect.push_back(stod(str));
        }
    } else {
        vect.push_back(stod(str));
        str = "";
    }

    cout << "printing vector" << endl;
    auto it = vect.begin();
    for (it; it != vect.end(); it++){
        std::cout << *it << ':';
    }
    return vect;
}/**
 * destructor
 */
OpenServerCommand::~OpenServerCommand(){}

/**
 * returnd a vector of matches in a line
 * @param str string
 * @return string with spaces between 2 tokens
 */
bool OpenServerCommand::regexMatches(string str) {
    string pattern = "([\\d\\.]+),?";

    auto matches = regexer(str, pattern);
    return matches.size() == 36;
}

vector<string> OpenServerCommand::regexer(string str, string pattern) {
    vector<string> matches;

    auto reg = regex(pattern);
    auto iter = sregex_iterator(str.begin(), str.end(), reg);
    auto ith = sregex_iterator();

    // loop the matches
    for (auto i = iter; i != ith; ++i) {
        int count = 0;
        for (string match : *i) {
            // skip empty matches
            if (match.empty()) {
                continue;
            }

            if (count > 0) {
                matches.push_back(match);
            }
            count++;
        }
    }

    cout << "rejex buffer matches" <<endl;
    auto it = matches.begin();
    for (it; it != matches.end(); it++)
        std::cout << *it << ':';

    return matches;
}

vector<double> OpenServerCommand::stringToDoubleVector(string str){
    myMutex.lock();
//    cout<< "string of the vector" << endl;
//    cout<< str << endl;
    string num = "";
    vector<double> vec;

    stringstream ss(str);
    string s;
//    cout << "start tokenazer" << endl;
    while (getline(ss, s, ',')) {
//        cout << s << "-";
        vec.push_back(stod(s));
    }
    cout << endl;
//    cout << "end tokenazer" << endl;

//    for(int i=0; i<= str.size() + 2  ; i++){
//        if(str[i] == ','){
//            i++;
//            vec.push_back(num);
//            num = "";
//        }
//        num +=str[i];
//    }
//    cout << "printing vector of doubles" << endl;
//    auto it = vec.begin();
//    for (it; it != vec.end(); it++)
//        std::cout << *it << '-';
    myMutex.unlock();
    return vec;


}
