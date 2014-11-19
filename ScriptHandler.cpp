#include "ScriptHandler.h"

//bool checkconditions(std::queue<std::string> separatedcodeline);
template <class T>
bool dooperation(T firstvariable, T secondvariable, string theoperator);

ScriptHandler::ScriptHandler()
{
  std::cout << "WARNING: Scripts cannot run functions without a passed handler";
  std::cout << "See documentation(doesn't exist) for how it should work\n";
  hasfunctionhandler = false;
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
          if(SCRIPTHANDLERDEBUG == true)
            std::cout << "got string " <<  tempstring << std::endl;
          inputstrings.push_back(tempstring);
          tempstring = "";
      }
      RunScript(inputstrings);
  }
}
ScriptHandler::ScriptHandler(std::function<void(string)> passedhandler)
{
    hasfunctionhandler = true;
    functionhandler = passedhandler;
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
            if(SCRIPTHANDLERDEBUG == true)
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
    //TODO: make a better, more intuitive process for math
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
    std::stack<int> locationoflastif;

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

        if(ignoreline == false && !separatedcodeline.empty()) //was ignoreline == false
        {

            //std::cout << "running code." << std::endl;

            //BUG IS DUE TO ENDIF ALWAYS SETTING IGNORELINETOFALSE
            //I HAVE TO KNOW IF AN IF STATEMENT WAS TRUE IN ORDER TO DO THAT
            if(separatedcodeline.front() == "if")
            {
                //if an if was run, add a location
                locationoflastif.push(currentline);
                //std::cout << "doing if code" << std::endl;
                separatedcodeline.pop();
                ignoreline = true;
                if(checkconditions(separatedcodeline))
                {
                    ignoreline = false;
                }
            }
            else if(separatedcodeline.front() == "while")
            {
                //std::cout << "running while code" << std::endl;
                separatedcodeline.pop();

                if(checkconditions(separatedcodeline))
                {
                    //cout << "PUSHING LINE" << currentline << endl;
                    locationoflastwhile.push(currentline);
                    //std::cout << "running while code" << std::endl;
                }
                else
                {
                    //cout << "flagging ignore line as true" << endl;
                    ignoreline = true;
                }

            }
            else if(separatedcodeline.front() == "int")
            {
                //int name data
                //integermodule tempmodule;
                //cout << "BEGININTEGER" << endl;
                string integername;
                int integerdata;

                separatedcodeline.pop(); // pop the int
                integername = separatedcodeline.front();
                //cout << "NAME: " << separatedcodeline.front() << endl;
                separatedcodeline.pop();// pop the name
                integerdata = atoi(separatedcodeline.front().c_str());
                //cout << "VALUE: " << integerdata << endl;
                //cout << "ENDINTEGER" << endl;

                //if I attempt to pop to clear the data, it crashes.  I don't know why

                //intvector.push_back(tempmodule);

                intmap[integername] = integerdata;
                //tempmodule = intvector[0];
                //std::cout << "name: " << tempmodule.integername << " value: " << tempmodule.integerdata << std::endl;

            }
            else if(separatedcodeline.front() == "float")
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
            else if(separatedcodeline.front() == "string")
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
            else if(separatedcodeline.front() == "math") //math varname operation
            {
              separatedcodeline.pop();
              //std::cout << "doing math code" << std::endl;
              std::string endvariable = separatedcodeline.front();
              separatedcodeline.pop();
              std::string operationstring;
              while(!separatedcodeline.empty())
              {
                operationstring = operationstring + separatedcodeline.front();
                separatedcodeline.pop();
              }
              intmap[endvariable] = domath(operationstring, intmap, stringmap, floatmap);

            }
            else if(separatedcodeline.front() == "function")
            {
              separatedcodeline.pop();
              if(hasfunctionhandler == true)
              {
                functionhandler(separatedcodeline.front());
                separatedcodeline.pop();
              }
              else
              {
                std::cout << "ERR: FUNCT LINE:" << codeline << " Function handler does not exist\n";
              }
            }
            else if(separatedcodeline.front() == "print")
            {
                std::string varstring;

                //std::cout << "running print code" << std::endl;
                separatedcodeline.pop();
                while(!separatedcodeline.empty())
                {
                  varstring = isvariabletype(separatedcodeline.front());
                  if(varstring == "false")
                  {
                    std::cout << separatedcodeline.front() << " ";
                  }
                  else if(varstring == "int")
                  {
                    std::cout << intmap[separatedcodeline.front()] << " ";
                  }
                  else if(varstring == "float")
                  {
                    std::cout << floatmap[separatedcodeline.front()] << " ";
                  }
                  else if(varstring == "string")
                  {
                    std::cout << stringmap[separatedcodeline.front()] << " ";
                  }
                  separatedcodeline.pop();
                }
                std::cout << std::endl;


            }
            else
            {
              //see if the number is a variable or something
            }
        }

        if(!separatedcodeline.empty())
        {
            if(separatedcodeline.front() == "endif")
            {
                //need to make this happen only if there was an if statement
                //std::cout << "found end of if loop";
                if(!locationoflastif.empty())
                {
                  ignoreline = false;
                  locationoflastif.pop();
                }
            }
            if(separatedcodeline.front() == "endwhile")
            {
                //std::cout << "found end of while loop";
                if(!locationoflastwhile.empty())
                {
                    ignoreline = false;
                    currentline = locationoflastwhile.top() - 1;
                    //cout << "GOTO LINE" << locationoflastwhile.top() - 1 << endl;
                    locationoflastwhile.pop();
                }
                else if(ignoreline == false)
                    std::cout<<"no while to co-respond to endwhile at line " << currentline + 1 << std::endl;
                else if(ignoreline == true)
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

bool ScriptHandler::checkconditions(std::queue<std::string> separatedcodeline)
{
  //start with void pointers
  //get a funcion that returns a pair: string and pointer
  //use string to turn all the below pointers into the appropriate

  string theoperator;
  string firstvariable;
  string secondvariable;

  bool isfirstavariable;
  bool issecondavariable;
  string comparetypes = "int";
  int firsti, secondi;
  string firsts, seconds;
  float firstf, secondf;

  //get the inputs
  firstvariable = separatedcodeline.front();
  separatedcodeline.pop();
  theoperator = separatedcodeline.front();
  separatedcodeline.pop();
  secondvariable = separatedcodeline.front();


  //figure out what exactly the inputs are
  //A is a variable type X, B isn't
  //A is a variable type X, B is a variable type X
  //A isn't, B is a variable type X

  if(intmap.find(firstvariable) != intmap.end())
  {
    firsti = intmap[firstvariable];
    isfirstavariable = true;
    comparetypes = "int";
  }
  if(floatmap.find(firstvariable) != floatmap.end())
  {
    firstf = floatmap[firstvariable];
    isfirstavariable = true;
    comparetypes = "float";
  }
  if(stringmap.find(firstvariable) != stringmap.end())
  {
    firsts = stringmap[firstvariable];
    isfirstavariable = true;
    comparetypes = "string";
  }

  //begin comparison of second variable
  if(intmap.find(secondvariable) != intmap.end())
  {
    secondi = intmap[secondvariable];
    issecondavariable = true;
    comparetypes = "int";
  }
  if(floatmap.find(secondvariable) != floatmap.end())
  {
    secondf = floatmap[secondvariable];
    issecondavariable = true;
    comparetypes = "float";
  }
  if(stringmap.find(secondvariable) != stringmap.end())
  {
    seconds = stringmap[secondvariable];
    issecondavariable = true;
    comparetypes = "string";
  }

  //if first wasn't a variable, assume it's of type the one that was a variable was
  if(isfirstavariable == false)
  {
    //check type, convert first to said type
    if(comparetypes == "int")
      firsti = atoi(firstvariable.c_str());
    if(comparetypes == "float")
      firstf = atof(firstvariable.c_str());
    if(comparetypes == "string")
      firsts = firstvariable;
  }

  //same as first
  if(issecondavariable == false)
  {
    //check type, convert second to said type
    if(comparetypes == "int")
      secondi = atoi(secondvariable.c_str());
    if(comparetypes == "float")
      secondf = atof(secondvariable.c_str());
    if(comparetypes == "string")
      seconds = secondvariable;
  }

  //run the comparisons default value will assume ints
  if(comparetypes == "int")
    return dooperation(firsti, secondi, theoperator);
  if(comparetypes == "float")
    return dooperation(firstf, secondf, theoperator);
  if(comparetypes == "string")
    return dooperation(firsts, seconds, theoperator);

}

template <class T>
bool dooperation(T firstvariable, T secondvariable, string theoperator)
{
  //cout << "First:" << firstvariable << " second: " << secondvariable << " OP: " << theoperator << endl;
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
  //std::cin.get();
  return false;
}

//returns if the string exists as a variable
//checks int, float, and bool variables though, be careful
std::string ScriptHandler::isvariabletype(std::string teststring)
{
  if(intmap.find(teststring) != intmap.end())
  {
    return "int";
  }
  else if(floatmap.find(teststring) != floatmap.end())
  {
    return "float";
  }
  else if(stringmap.find(teststring) != stringmap.end())
  {
    return "string";
  }
  return "false";
}
