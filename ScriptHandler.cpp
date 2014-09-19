#include "ScriptHandler.h"

bool checkconditions(std::queue<std::string> separatedcodeline);

ScriptHandler::ScriptHandler()
{
    std::vector<std::string> inputstrings;
    std::ifstream scriptfile;
    scriptfile.open("Script.txt");
    if(scriptfile.fail())
        std::cout << "file failed to open";
    else
    {
        int i = 0;
        std::string tempstring;
        while(getline(scriptfile, tempstring))
        {
            //getline(scriptfile, tempstring);
            std::cout << "got string " <<  tempstring << std::endl;
            inputstrings.push_back(tempstring);
            tempstring = "";
        }
        RunScript(inputstrings);
    }
}

void ScriptHandler::OpenFileAtLine(std::string file, std::string line)
{

}

void ScriptHandler::RunScript(std::vector<std::string> scriptdata)
{
    //std::cout << "got dem strings! See? " <<  scriptdata[3] << std::endl;
    //create stringstream
    //split the stringstream into parts
    //use those parts to run commands
    /*std::vector<integermodule> intvector;
    std::vector<floatmodule> floatvector;
    std::vector<stringmodule> stringvector;*/

    std::stringstream codeline;
    std::queue<std::string> separatedcodeline;
    int currentline = 0;
    int positioncursora = 0;
    int positioncursorb = 0;
    bool ignoreline = false;
    std::string tempstring = "";
    std::stack<int> locationoflastwhile;

    while(currentline < scriptdata.size()) //so long as there is a new line of code in the script
    {
        codeline.str("");
        codeline.clear();
        codeline.str(scriptdata[currentline]);
        //std::cout << "codeline contains " << codeline.str() << std::endl;

        while(codeline >> tempstring) //separate the line of code
        {
            //codeline >> tempstring;
            separatedcodeline.push(tempstring);
            //std::cout << "separated " << separatedcodeline.back() << std::endl;
        }

        if(!ignoreline) //was ignoreline == false
        {
            //std::cout << "running code." << std::endl;
            if(separatedcodeline.front() == "if")
            {
                //std::cout << "doing if code" << std::endl;
                separatedcodeline.pop();
                ignoreline = true;
                if(checkconditions(separatedcodeline))
                {
                    ignoreline = false;
                }
            }
            if(separatedcodeline.front() == "while")
            {
                //std::cout << "running while code" << std::endl;
                separatedcodeline.pop();
                if(checkconditions(separatedcodeline) == true)
                {
                    locationoflastwhile.push(currentline);
                    std::cout << "running while code" << std::endl;
                }
                else
                {
                    ignoreline = true;
                }

            }
            if(separatedcodeline.front() == "int")
            {
                //int name data
                //integermodule tempmodule;
                string integername;
                int integerdata;

                separatedcodeline.pop(); // pop the int
                integername = separatedcodeline.front();
                separatedcodeline.pop();// pop the name
                integerdata = atoi(separatedcodeline.front().c_str());
                //if I attempt to pop to clear the data, it crashes.  I don't know why

                //intvector.push_back(tempmodule);

                intmap[integername] = integerdata;
                //tempmodule = intvector[0];
                //std::cout << "name: " << tempmodule.integername << " value: " << tempmodule.integerdata << std::endl;

            }
            if(separatedcodeline.front() == "float")
            {
              //std::cout << "begin float";
              //floatmodule tempmodule;
              string floatname;
              float floatdata;

              separatedcodeline.pop(); //pop the float
              floatname = separatedcodeline.front();
              separatedcodeline.pop();
              floatdata = atof(separatedcodeline.front().c_str());

              //floatvector.push_back(tempmodule);
              floatmap[floatname] = floatdata;
              //tempmodule = floatvector[0];
              //std::cout << "name: " << tempmodule.floatname << " value: " << tempmodule.floatdata << std::endl;

            }
            if(separatedcodeline.front() == "string")
            {
              //stringmodule tempmodule;
              string stringname;
              string stringdata;

              separatedcodeline.pop(); //pop the float
              stringname = separatedcodeline.front();
              separatedcodeline.pop();
              stringdata = separatedcodeline.front();

              //stringvector.push_back(tempmodule);
              stringmap[stringname] = stringdata;
              cout << stringmap[stringname] << "TESTING" << endl;
              //std::cout << tempmodule.stringname << tempmodule.stringdata;
            }
            if(separatedcodeline.front() == "print")
            {
                //std::cout << "running print code" << std::endl;
                separatedcodeline.pop();
                while(!separatedcodeline.empty())
                {
                std::cout << separatedcodeline.front() << " ";
                separatedcodeline.pop();
                }
                std::cout << std::endl;
            }
        }

        if(!separatedcodeline.empty())
        {
            if(separatedcodeline.front() == "endif")
            {
                //std::cout << "found end of if loop";
                ignoreline = false;
            }
            if(separatedcodeline.front() == "endwhile")
            {
                //std::cout << "found end of while loop";
                if(!locationoflastwhile.empty())
                {
                    currentline = locationoflastwhile.top() - 1;
                    locationoflastwhile.pop();
                }
                else if(locationoflastwhile.empty() == true && ignoreline == false)
                    std::cout<<"no while to co-respond to endwhile at line " << currentline + 1 << std::endl;
                else if(locationoflastwhile.empty() == true && ignoreline == true)
                    ignoreline = false;

            }
            //if the front value is equal to any variable look for more things
            //lets make the variable lists into maps first
        }


        //after all the stuff is read and done with, delete the current queue.
        while(separatedcodeline.empty() == false)
        {
            separatedcodeline.pop();
        }
        //while(locationoflastwhile.empty() == false)
        //{
        //    locationoflastwhile.pop();
        //}
        //if I want to move the cursor, change currentline + or -;
        currentline++;
    }

}




//pre: needs a separatedcodeline with at least 3 variables.  1st number, second operator, third number
//post: performs operation and returns true or false

//this is where I need to get variables, for now.
//if(intmap.find(intigername) == m.end())
bool checkconditions(std::queue<std::string> separatedcodeline)
{
                int firstvariable;
                std::string theoperator;
                int secondvariable;
                std::stringstream(separatedcodeline.front()) >> firstvariable;
                separatedcodeline.pop();
                theoperator = separatedcodeline.front();
                separatedcodeline.pop();
                std::stringstream(separatedcodeline.front()) >> secondvariable;

                    if (theoperator == "=")
                    {
                        if(firstvariable == secondvariable)
                            return true;
                    }
                    if (theoperator == "!=")
                    {
                        if(firstvariable != secondvariable)
                            return true;
                    }
                    if (theoperator == ">")
                    {
                        if(firstvariable > secondvariable)
                            return true;
                    }
                    if (theoperator == "<")
                    {
                        if(firstvariable < secondvariable)
                            return true;
                    }
                    if (theoperator == ">=")
                    {
                        if(firstvariable >= secondvariable)
                            return true;
                    }
                    if (theoperator == "<=")
                    {
                        if(firstvariable <= secondvariable)
                            return true;
                    }
                    return false;
}
