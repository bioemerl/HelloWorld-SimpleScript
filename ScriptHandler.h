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
#include <map>
#include <functional>
#include "MathHandler.h"

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::pair;

const bool SCRIPTHANDLERDEBUG = false;

bool isvariable(std::string teststring);
//I want to do these things
//D: D:if, D:while done
//D:conditionals, D:addition, D:subtraction, D:multiplicatoin, D:devision
//Make variables and numbers replace one another done
//"open file and go to line X"
//D:run functions from other classes that are included

//NOTE: Functions have to be let run by making a functionhandler function in the
//bottom of the main program of the thing that is running this class
//the functionhandler must take a string, and the user of this class
//decides where to and what to do with the string they get when function X is typed

//start script at some trigger points

class ScriptHandler
{
    public:
        ScriptHandler();
        ScriptHandler(std::function<void(std::string)> passedhandler);
        void OpenFileAtLine(string file, string line);
        void RunScript(std::vector<string> scriptdata);
        bool checkconditions(std::queue<std::string> separatedcodeline);
        std::string isvariabletype(std::string teststring);
    private:
        int Iwantaprivatevariable;
        bool hasfunctionhandler;
        std::function<void(string)> functionhandler;
        map<string, int> intmap;
        map<string, std::string> stringmap;
        map<string, float> floatmap;
};

#endif // SCRIPTHANDLER_H
