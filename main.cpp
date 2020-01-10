#include <iostream>
#include <vector>
#include "Lexer.h"
#include "Parser.h"
#include "SymbolTable.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "SleepCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"

/**
 * This is the main class.
 * befre use don't forget to include the fly.txt in the arguments
 * @param argc
 * @param argv The function receives input within the argv representing a file name
 * @return int 0 if all goes well.
 */
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Invalid amount of arguments";
        exit(EXIT_FAILURE);
    }

    string str = argv[1];
    Lexer lex;
    //create a vector of all commands and values
    vector<string> vect = lex.createVectorFromFile(str);


    //initialize the commands map
    SymbolTable::getInstance() -> allCommandsMap =
                                    {{"openDataServer",       new OpenServerCommand(vect)},
                                    {"connectControlClient", new ConnectCommand(vect)},
                                    {"var",                  new DefineVarCommand(vect)},
                                    {"if",                   new IfCommand(vect)},
                                    {"while",                new WhileCommand(vect)},
                                    {"Sleep",                new SleepCommand(vect)},
                                    {"Print",                new PrintCommand(vect)}
    };
    Parser pars;
    //set the lexer vactor and index = 0 to rhe parser
    pars.addVaribles(vect, 0);

    //interprate the commands
    pars.parse();


    return 0;
}
