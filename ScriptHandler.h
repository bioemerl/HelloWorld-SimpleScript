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


//I want to do these things
//D: D:if, D:while
//D:conditionals, addition, subtraction, multiplicatoin, devision
//TODO: Make variables and numbers replace one another
//"open file and go to line X"
//run functions from other classes that are included
//start script at some trigger points

//to use a string to cal a function
//use a map ["functionname"] = functionname(int a, int b)
//then do int i = map["functionname"](1, 2);
//then just map (heh) all the function you want to be able to run to the map

//for a pointer that can point to anything use void * X;
//to do *X then you have to typecast so void* anypointer
//int i;  anypointer = &i;  int j = *(int*)anypointer

class ScriptHandler
{
    public:
        ScriptHandler();
        void OpenFileAtLine(string file, string line);
        void RunScript(std::vector<string> scriptdata);
        bool checkconditions(std::queue<std::string> separatedcodeline);
    private:
        int Iwantaprivatevariable;

        //TODO: I learned that maps exist, replace these with maps.
        /*struct integermodule{
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
        };*/
        map<string, int> intmap;
        map<string, std::string> stringmap;
        map<string, float> floatmap;
};

#endif // SCRIPTHANDLER_H
