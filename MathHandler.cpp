//Ways to handle exponents
//situation one X^3 easy
//situation two (X+5)^3 hard
//situation sin(x)^3 even harder
//going to ignore situation three
//possible solutions
//1.  find areas with )^# and run the domath() on the parens, replace parens with number
//2.  Find and treat ^ as an operator
//3.  don't allow exponents at all
//4.  don't allow exponents after a parens (x + 5)^2 is not x^2 + 5 ^2
//5.  make ^2 a "repeat operator" that makes the previous operatoer add into the string X times
//6.  (5^2) => (5*5) 5^3 => (5*5*5)
//would only work for pos int exponents
//if negative make 1/(5^3)
//
#include "MathHandler.h"




int domath(std::string thestring, std::map<std::string, int> intmap, std::map<std::string, std::string> stringmap, std::map<std::string, float> floatmap)
{
	//thestring = removespaces(thestring);
	thestring = turnvarstovals(thestring, intmap, stringmap, floatmap);
	return mathhandler(thestring);
}

//TODO:1  Replace all non-letter values with numbers
//first step is to find a letter
//second is to find all letters after that
//third is to condense those letters into a string,
//find that string as a variable,
//and replace the letters with that number

//TODO:2 find all exponents, repeat previous item X number of times 5^3 = "5" + "*5*5"
//find any ^
//find the number after the ^
//find the number(s) before the ^,
std::string turnvarstovals(std::string thestring, std::map<std::string, int> intmap, std::map<std::string, std::string> stringmap, std::map<std::string, float> floatmap)
{
	if(DEBUG == true)
	{
		std::cout << "____VARSTOVALS_____" << std::endl;
	}
	std::string letters = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz";
  std::string variablestring;
	int firstpos = 0;
	int secondpos = -1;
	for(int i = 0; i < thestring.size(); i++) //loops through the whole string
	{
		//reset the position values
		firstpos = 0;
		secondpos = -1;
    //TODO: STEP ONE, GET THE VARIABLE
		//std::cout << i << std::endl;
    if(isalpha(thestring[i])) //trigger on the first letter
    {
			if(DEBUG == true)
				std::cout << "found alpha " << thestring[i] << " at" << i << std::endl;
      firstpos = i;
      secondpos = thestring.find_first_not_of(letters); //find the first non-character
			if(DEBUG == true)
			{
				std::cout << "firstposition " << firstpos << std::endl;
				std::cout << "secondposition " << secondpos << std::endl;
			}
		}
		if(secondpos >= 0 && secondpos <= thestring.size()) //check if the string found any letters
		{
			if(DEBUG == true)
				std::cout << "Running code to convert variable to number" << std::endl;
    	//I should have the first string of characters.  I now want to make two strings.
    	//one with the normal numbers, one with the string.
    	//TODO: now I need to use this to find the number I need
    	variablestring = thestring.substr(firstpos, secondpos-firstpos);
			thestring = thestring.substr(0, firstpos) + thestring.substr(secondpos);
			if(DEBUG == true)
				std::cout << "Found variable: " << variablestring << std::endl;
			//TODO:
			//now I need the number I want,
			//then I want to insert that number into the string at firstpos
			//I am currently passing stringmap, intmap, and floatmap to this function.
			int repvar;
			float frepvar;
			std::string srepvar;
			if(intmap.find(variablestring) != intmap.end())
			{
				repvar = intmap[variablestring];
				std::stringstream constr;
				constr << repvar;
				std::string therepvar = constr.str();
				thestring = thestring.substr(0, i) + therepvar + thestring.substr(i);
			}
			else if(stringmap.find(variablestring) != stringmap.end())
			{
				srepvar = stringmap[variablestring];
				thestring = thestring.substr(0, i) + srepvar + thestring.substr(i + srepvar.size());
			}
			else if(floatmap.find(variablestring) != floatmap.end())
			{
				std::stringstream fconstr;
				fconstr >> frepvar;
				std::string thefrepvar = fconstr.str();
				frepvar = floatmap[variablestring];
				thestring = thestring.substr(0, i) + thefrepvar + thestring.substr(i + thefrepvar.size());
			}
			if(DEBUG == true)
				std::cout << "Completed string: " << thestring << std::endl;

		}

    //STEP TWO: FIND EXPONENTS
    if(thestring[i] == '^')
    {
      //DONE: find and replicate areas of (2x+5)^5
			int power = thestring[i + 1] - '0';  //store the power as an integer
			thestring = thestring.substr(0, i) + thestring.substr(i+2); //remove the ^x from the string
			std::string replicatestring;
			//i = i - 2; //adjust i back to account for the removed two characters
			if(thestring[i-1] == ')')
			{
				//find the opening parens
				int locofcloseparens = i;
				int locofopenparens = -1;
				for(int j = i; j  > 0; j--)
				{
					if(thestring[j] == '(')
					{
						locofopenparens = j;
						break;
					}
				}
				if(locofopenparens == -1)
				{
					std::cerr << "Failed to find Opening Parens for exponential operator" <<std::endl;
				}
				//Begin process of replicating what is in the parens
				//std::cout << locofopenparens << " " << locofcloseparens << std::endl;
				replicatestring = thestring.substr(locofopenparens, locofcloseparens - locofopenparens);
				//std::cout << replicatestring <<std::endl;
			}
			else
			{
				replicatestring = std::string(1, thestring[i - 1]); //store the thing to be exponential
			}

			for(int j = 0; j < power - 1; j++) //loop one less than the power, to add the number of times X has to be multiplied
			{
				thestring = thestring.substr(0, i) + "*" + replicatestring + thestring.substr(i); //add in the power and the multiple
				i = i + 2; // adjust I for the new string size
				//std::cout << thestring << std::endl; //debug
			}
    }

	}
	if(DEBUG == true)
	{
		std::cout << "returning " << thestring <<std::endl;
		std::cout << "____ENDVARSTOVALS_____" << std::endl;
	}
	return thestring;
}



//TODO: should be working, honestly, I hope.
//TODO: make the function work with things other than int
//TODO: devide this massive fucking thing into sub-parts.
int mathhandler(std::string thestring)
{
	//std::cout << "--------------" << std::endl;
	//std::cout << thestring << std::endl;

	//find if there is a ) that is not the last character in the string
	for(int i = 0; i < thestring.size(); i++)
	{
		if((thestring[i] == ')' || thestring[i] == '(') && (i != thestring.size() - 1))
			break;
		else if(thestring[i] == ')' && (i == thestring.size() - 1))
		{ //if there is not remove the () from the string
			thestring = thestring.substr(1, thestring.size() - 2);
			//std::cout << thestring << std::endl;
		}
	}

	//find the place to split at
	int ignorelines = 0;
	std::string highestfound = "";
	int splitlocation = 0; // the first value should never be an operator

	for(int i = 0; i < thestring.size(); ++i)
	{
		if(ignorelines == 0)
		{
			if(thestring[i] == '(')
			{
				ignorelines++;
				//std::cout << "ignorelines " << ignorelines << std::endl;
			}
			else if(thestring[i] == '+')
			{
				highestfound = "+";
				splitlocation = i;
			}
			else if(thestring[i] == '-')
			{
				if(highestfound != "+")
				{
					highestfound = "-";
					splitlocation = i;
				}
			}
			else if(thestring[i] == '/')
			{
				if(highestfound != "+" && highestfound != "-")
				{
					highestfound = "/";
					splitlocation = i;
				}
			}
			else if(thestring[i] == '*')
			{
				if(highestfound != "+" && highestfound != "-" && highestfound != "/")
				{
					highestfound = "*";
					splitlocation = i;
				}
			}
		}
		else
		{
			if(thestring[i] == ')')
			{
				ignorelines--;
				//std::cout << "ignorelines " << ignorelines << std::endl;
			}
			if(thestring[i] == '(')
				ignorelines++;
			/*if((thestring[i] == '=' || thestring[i] == '/' || thestring[i] == '|' || thestring[i] == '&') && splitlocation == 0)
			{
				if(thestring[i+1] == '(')
					splitlocation = i;
			}*/
		}
	}

	//std::cout << splitlocation << std::endl;
	if(splitlocation == 0) //if no operators were found in the string
	{
		//if no ops are found, it could be two cases
		//1 (35+34)
		//2 24
		//case 1, continue recursion
		//case 2, return the int
		//if case one
		if(thestring[0] == '(' && thestring[thestring.size()-1] == ')')
			return mathhandler(thestring.substr(1, thestring.size()-2)); //the string minus the ()
		else //if case 2
		{
			//std::cout << "Returning " <<  std::atoi(thestring.c_str()) << std::endl;
			return std::atoi(thestring.c_str());
		}

		return 0;
	}
	else //if operators were found in the string
	{
		char theoperator = thestring[splitlocation];
		//std::cout << "operator = " << theoperator << std::endl;
		//I need to switch this and go through every possible operator, returning what is needed
		//'=' leads to return function(left) = function(right)

		switch(theoperator){
			case '*':
				//std::cout << "calculating *" << std::endl;
				return (mathhandler(thestring.substr(0, splitlocation)) * mathhandler(thestring.substr(splitlocation + 1)));
				break;
			case '/':
				//std::cout << "calculating /" << std::endl;
				return ((mathhandler(thestring.substr(0, splitlocation))) / mathhandler(thestring.substr(splitlocation + 1)));
				break;
			case '+':
				//std::cout << "calculating +" << std::endl;
				//std::cout << thestring.substr(splitlocation + 1) << std::endl;
				return (mathhandler(thestring.substr(0, splitlocation)) + mathhandler(thestring.substr(splitlocation + 1)));
				break;
			case '-':
				//std::cout << "calculating -" << std::endl;
				return ( (mathhandler(thestring.substr(0, splitlocation))) -  (mathhandler(thestring.substr(splitlocation + 1))) );
				break;
		}

	}
}

std::string removespaces(std::string thestring)
{
	if(DEBUG == true)
		std::cout << "Before removal: " << thestring << std::endl;
	for(int i = 0; i < thestring.size(); i++)
	{
		if(thestring[i] == ' ')
		{
			thestring = thestring.substr(0, i) + thestring.substr(i+1);
		}
	}
	if(DEBUG == true)
		std::cout << "Removed spaces: " << thestring << std::endl;
	return thestring;
}
