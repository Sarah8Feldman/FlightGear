# FlightGear

First milestone - Advanced programming 2019\20
## Preview

#### Link To The GitHub Project: https://github.com/Sarah8Feldman/FlightGear

The FlightGear project connect to the simulator and fly the airplan with the commands in text file.
In the project we have argument that contains different commands.

At first we created a Lexer that aims to read a file that contains code, and returns the code to a string of strings.

We have now used CommandPattem and Map to link array strings to a Command object.

We use maps to get a value by o(1).
The map contains keys and values.
The keys are strings and the values are a specific object of type Command.

Given a string, we can immediately pull out the command that needs to be executed.

There is a class called Parser that aims to go through all the strings in the array and pull out 
using the Command Object string and call its execute.

## Elements

    Design Patters
    Client-Server architecture
    Working with files
    Working with threads
    Data structures
    
## Set FlightGear Simulator

1. Open The FlightGear Simulator.
2. Click On Settings.
3. Go To Additional Settings.
4. type the following commands:

    * --telnet=socket,in,10,127.0.0.1,5402,tcp=8080
    
    * --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small

## Command Classes
### ~ Command

The Command class is a interface class that contain execute function that we will run for all the command class.
### ~ ConnectCommand

The ConnectCommand class is a command in which we send and update values to the simulator.
We act as a client who sends requests to the simulator.
### ~ OpenServerCommand

The OpenServerCommand class gets data from the server about flight variables and updates them to our map.
The simulator connects to the server as client and sends requests.
### ~ Map

The Map class have map that contains string and command*.
### ~ DefineVar

The DefineVar class creates variables with path to simulator and value.
To execute we have number of cases:
 * 1. new vae definition - create a variable whith a path so simulation.
 * 2. create a var whithout a path to simulation.
 * 3. update a variable's value.
### ~ Sleep

The Sleep class sends thread to sleep for a spesific time(amount of time in milliseconds).
### ~ Print

The Print class prints a value that it excepts.
To execute we have 2 cases:
 * 1. print a string in between "".
 * 2. print a value of a variable(can be an expression).
### ~ If

The If class represent a If loop.
To execute: if the condition is valid execute all of the commands inside the scope.
### ~ While

The While class represent a while loop.
To execute: if the condition is valid execute all of the commands inside the scope.
### ~ Expression

The Expression class simplify an expression.

## Architecture Classes

### ~ Lexer

The Lexer class that aims to read a file that contains code, and returns the code to a string of strings.
### ~ Parser

The Parser class that aims to go through all the strings in the array and pull out 
using the Command Object string and call its execute.
### ~ SymbolTable

The SymbolTable class contains map that updates from the server.
The class have mutex that used for controlling the threads access to the symbol table.

## Authors

#### * Adi Ziv

    Submit name : Adi10z

#### * Sarit Feldman

    Submit name : Sarah8Feldman
    
    
 BIU University, Israel.

