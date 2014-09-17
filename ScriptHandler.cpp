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
    std::vector<integermodule> intvector;
    std::vector<floatmodule> floatvector;
    std::vector<stringmodule> stringvector;
    //std::vector<int>
    //std::vector<int>
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

        if(ignoreline == false)
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
                integermodule tempmodeule;

                separatedcodeline.pop(); // pop the int
                tempmodeule.integername = separatedcodeline.front();
                separatedcodeline.pop();// pop the name
                tempmodeule.integerdata = atoi(separatedcodeline.front().c_str());
                //if I attempt to pop to clear the data, it crashes.  I don't know why

                std::cout << "name: " << tempmodeule.integername << " value: " << tempmodeule.integerdata << std::endl;

                intvector.push_back(tempmodeule);
                tempmodeule = intvector[0];


            }
            if(separatedcodeline.front() == "float")
            {

            }
            if(separatedcodeline.front() == "string")
            {

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
