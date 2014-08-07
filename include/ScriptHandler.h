#ifndef SCRIPTHANDLER_H
#define SCRIPTHANDLER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <stack>

//I want to do these things
//if, while
//conditionals, addition, subtraction, multiplicatoin, devision
//"open file and go to line X"
//run functions from other classes that are included
//start script at some trigger points

class ScriptHandler
{
    public:
        ScriptHandler();
        void OpenFileAtLine(std::string file, std::string line);
        void RunScript(std::vector<std::string> scriptdata);
    private:
        int Iwantaprivatevariable;
};

#endif // SCRIPTHANDLER_H
