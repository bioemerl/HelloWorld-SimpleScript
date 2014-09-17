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
//D: D:if, D:while
//D:conditionals, addition, subtraction, multiplicatoin, devision
//TODO: Make variables and numbers replace one another
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
        struct integermodule{
          int integerdata;
          std::string integername;
        };
        struct stringmodule{
          std::string stringdata;
          std::string stringname;
        };
        struct floatmodule{
          float floatdata;
          std::string floatname;
        };
};

//untill I can get this to work, I have to do this
#include "ScriptHandler.cpp"
#endif // SCRIPTHANDLER_H
