# FlightGear
First milestone - Advanced programming 2019\20
## Preview
Link To GitHub Project:

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

## Elements:

    Design Patters
    Client-Server architecture
    Working with files
    Working with threads
    Data structures
    
## Set FlightGear Simulator

1. Open FlightGear Simulator.
2. Click Settings
3. Scroll down to Additional Settings
4. type the following commands:

    --telnet=socket,in,10,127.0.0.1,5402,tcp=8080
    
    --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small


