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
#include "MathHandler.h"

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::pair;

bool isvariable(std::string teststring);
//I want to do these things
//D: D:if, D:while done
//D:conditionals, addition, subtraction, multiplicatoin, devision
//Make variables and numbers replace one another done
//"open file and go to line X"
//run functions from other classes that are included
//start script at some trigger points

class ScriptHandler
{
    public:
        ScriptHandler();
        void OpenFileAtLine(string file, string line);
        void RunScript(std::vector<string> scriptdata);
        bool checkconditions(std::queue<std::string> separatedcodeline);
        std::string isvariabletype(std::string teststring);
    private:
        int Iwantaprivatevariable;

        map<string, int> intmap;
        map<string, std::string> stringmap;
        map<string, float> floatmap;
};

#endif // SCRIPTHANDLER_H
