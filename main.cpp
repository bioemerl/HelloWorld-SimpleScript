#include <iostream>
#include "ScriptHandler.h"
#include <string>

using namespace std;

void functionhandler(std::string handlerstring);
void printfu(std::string thestring);

int main()
{
    ScriptHandler testing(functionhandler);
    int test;
    cin >> test;
    return 0;
}

void printfu(std::string thestring){
  std::cout << thestring << std::endl;
}

void functionhandler(std::string handlerstring){
  printfu(handlerstring);

}
