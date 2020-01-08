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

SymbolTable* myTable = new SymbolTable();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Invalid amount of arguments";
        exit(EXIT_FAILURE);
    }

    string str = argv[1];
    Lexer lex;
    vector<string> vect = lex.createVectorFromFile(str);
//    cout << "printing vector" << endl;
//    auto it = vect.begin();
//    for (it; it != vect.end(); it++){
//        std::cout << *it << endl;
//    }

    int index = 0;
    myTable -> allCommandsMap = {{"openDataServer", new OpenServerCommand(vect)},
                                 {"connectControlClient", new ConnectCommand(vect)},
                                 {"var", new DefineVarCommand(vect)},
                                 {"if", new IfCommand(vect)},
                                 {"while", new WhileCommand(vect)},
                                 {"Sleep", new SleepCommand(vect)},
                                 {"Print", new PrintCommand(vect)}
    };
    Parser pars;
    pars.addVaribles(vect, 0);
    myTable -> serverIsUp = false;
    pars.parse();


//    myTable -> serverThread.join();
//    myTable -> clientTread.join();

    return 0;
}
