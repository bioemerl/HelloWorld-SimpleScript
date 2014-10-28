SimpleScript.exe: main.cpp MathHandler.o ScriptHandler.o
	g++ -std=c++11 -s main.cpp MathHandler.o Scripthandler.o -o SimpleScript.exe

MathHandler.o: MathHandler.h MathHandler.cpp
	g++ -std=c++11 -c MathHandler.cpp -o MathHandler.o

ScriptHandler.o: ScriptHandler.h ScriptHandler.cpp
	g++ -std=c++11 -c ScriptHandler.cpp -o ScriptHandler.o
