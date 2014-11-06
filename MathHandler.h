#ifndef MATH_HANDLER_H
#define MATH_HANDLER_H

#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>

//TODO: make this handle variables
const bool DEBUG = true;
std::string removespaces(std::string thestring);
std::string turnvarstovals(std::string thestring, std::map<std::string, int> intmap, std::map<std::string, std::string> stringmap, std::map<std::string, float> floatmap);
int mathhandler(std::string thestring);
int domath(std::string thestring, std::map<std::string, int> intmap, std::map<std::string, std::string> stringmap, std::map<std::string, float> floatmap);

#endif
