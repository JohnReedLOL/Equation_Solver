/*! \file Equation_Solver.cpp
 \brief Defines all the methods of the Equation_Solver program except for main.
 */
/*
 This file, Equation_Solver.cpp is part of the Equation_Solver source.

 Equation_Solver is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Equation_Solver is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Equation_Solver. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Equation_Solver.h"
#include <cctype>

char * parenthesize(char * equation)
{
	int counter1 = 0;
	int counter2 = 0;
	int counter3 = 0;

	bool inputInvalid = false;
	for (char * i = equation; *i != '\0'; ++i)
	{
		if (((int) (*i)) < 32 || ((int) (*i)) > 125 || *i == '!' || ((int) (*i)) == 34 || *i == '#' || *i == '$'
				|| *i == '&' || ((int) (*i)) == 39 || ((int) (*i)) == 44 || *i == ':' || *i == '?' || *i == '@'
				|| ((int) (*i)) == 92 || *i == '_' || ((int) (*i)) == 96 || *i == '|')
		{
			std::cerr << "Error! I do not understand the \"" << (*i) << "\" symbol." << std::endl;
			inputInvalid = true;
		}

		if (*i == '{')
			++counter1;
		else if (*i = '}')
			--counter1;

		if (*i == '(')
			++counter2;
		else if (*i = ')')
			--counter2;

		if (*i == '[')
			++counter3;
		else if (*i = ']')
			--counter3;
	}

	if (counter1 != 0)
	{
		if (counter1 > 0)
			std::cerr << "Error! More open braces than closed braces. " << std::endl;
		else
			std::cerr << "Error! More closed braces than open braces. " << std::endl;
		inputInvalid = true;
	}
	else if (counter1 != 0)
	{
		if (counter1 > 0)
			std::cerr << "Error! More open parenthesis than closed parenthesis. " << std::endl;
		else
			std::cerr << "Error! More closed parenthesis than open parenthesis. " << std::endl;
		inputInvalid = true;
	}
	if (counter1 != 0)
	{
		if (counter1 > 0)
			std::cerr << "Error! More open brackets than closed brackets. " << std::endl;
		else
			std::cerr << "Error! More closed brackets than open brackets. " << std::endl;
		inputInvalid = true;
	}

	if (inputInvalid == true)
		return nullptr;

	char * open_paren_ptr = equation;
	char * closed_paren_ptr = 0;

	char * open_bracket_ptr = equation;
	char * closed_bracket_ptr = 0;

	char * i;
	for (i = equation; (*i != ')') && (*i != '\0') && (*i != '='); ++i)
	{
		if (*i == '(')
			open_paren_ptr = i;
	}

	if (*i == ')')
	{
		closed_paren_ptr = i;
		i = open_paren_ptr;
	}
	else if (*i == '=')
	{
		closed_paren_ptr = i;

		if( (open_paren_ptr != equation) )
		{
			std::cerr << "Error! Your left parenthesis is off!" << std::endl;
			inputInvalid = true;
		}
		while(*i != '\0')
		{
			++i;
		}
		--i;
		if( *i != ')' )
		{
			std::cerr << "Error! Your right parenthesis is off!" << std::endl;
			inputInvalid = true;
		}
		if (inputInvalid == true)
			return nullptr;

		i = open_bracket_ptr;
	}
	else //*i == '\0'
	{
		closed_paren_ptr = i;
		i = equation;
	}

	char * j;
	for (j = equation; (*j != ']') && (*j != '\0') && (*j != '='); ++i)
	{
		if (*j == '[')
		open_bracket_ptr = j;
	}

	if (*j == ']')
	{
		closed_bracket_ptr = i;
		j = open_bracket_ptr;
	}
	else if (*j == '=')
	{
		closed_bracket_ptr = j;

		if( (open_bracket_ptr != equation) )
		{
			std::cerr << "Error! Your left bracket is off!" << std::endl;
			inputInvalid = true;
		}
		while(*j != '\0')
		{
			++j;
		}
		--j;
		if( *j != ']' )
		{
			std::cerr << "Error! Your right bracket is off!" << std::endl;
			inputInvalid = true;
		}
		if (inputInvalid == true)
			return nullptr;

		j = open_bracket_ptr;
	}
	else //*j == '\0'
	{
		closed_paren_ptr = i;
		j = equation;
	}

	if( (open_paren_ptr < open_bracket_ptr && closed_paren_ptr < closed_bracket_ptr)
			|| (open_paren_ptr > open_bracket_ptr && closed_paren_ptr > closed_bracket_ptr))
	{
		std::cerr << "The parenthesis and brackets are mixed up" << std::endl;
		return nullptr;
	}
//Now we have to check if there are any illegal variable, constant, or function names.

//Now look to see which operators are between the parenthesis
//Or if no parenthesis, take the first operator and assume left to right order of operations.

}

int check_names(char * equation)
{
	for(char * i = equation; *i != '\0'; ++i)
	{
		//if one letter is lowercase, it must be a variable or one of the three reserved mathematical constants e (2.71828182845904523536), pi(3.14159...), i (-1^(1/2)), or .
		//Post inspection, all variables will be prepended with a @.
		//Variables cannot be given a permanent value because then they would be constants.
		//Built in constants will be prepended with a "~".
		if( (std::islower(*i)) )
		{
			++i;
			for(;*i != '+' || *i != '-' || *i != '*' || *i != '/' || *i != '%' || *i != '!'
					|| *i != '^' || *i != '(' || *i != ')' || *i != '[' || *i != ']' || *i != '{' || *i != '}'
					|| *i != ';' || *i != '<' || *i != '>' || *i != '='
					|| !((*i == 'A')&&(*(i+1) == 'N')&&(*(i+2)=='D'))
					|| !((*i == 'O')&&(*(i+1) == 'R'))
					|| !((*i == 'X')&&(*(i+1) == 'O')&&(*(i+2)=='R'))
					|| !((*i == 'N')&&(*(i+1) == 'O')&&(*(i+2)=='T'))
					|| !((*i == 'I')&&(*(i+1) == 'F'))
					|| !((*i == 'I')&&(*(i+1) == 'F')&&(*(i+1) == 'F'))
					|| !((*i == 'T')&&(*(i+1) == 'R')&&(*(i+2)=='U')&&(*(i+3)=='E'))
					|| !((*i == 'F')&&(*(i+1) == 'A')&&(*(i+2)=='L')&&(*(i+3)=='S')&&(*(i+4)=='E'))
				;++i)
			{
				if(std::isupper(*i))
				{
					std::cerr << "Variable names must start with a lowercase letter and cannot contain uppercase letters." << std::endl;
					return 1;
				}
				else if(std::isdigit(*i) )
				{
					if(std::isalpha(*(i-1) ) )
					{
						std::cerr << "Numbers can only go at the very end of variable names." << std::endl;
						return 1;
					}
				}
			}
			//Go to the end of the logical word.
			if((*i == 'A')&&(*(i+1) == 'N')&&(*(i+2)=='D')) i+=2;
			else if ((*i == 'O')&&(*(i+1) == 'R')) ++i;
			else if ((*i == 'X')&&(*(i+1) == 'O')&&(*(i+2)=='R')) i+=2;
			else if ((*i == 'N')&&(*(i+1) == 'O')&&(*(i+2)=='T')) i+=2;
			else if ((*i == 'I')&&(*(i+1) == 'F')) ++i;
			else if ((*i == 'I')&&(*(i+1) == 'F')&&(*(i+1) == 'F')) i+=2;
			else if ((*i == 'T')&&(*(i+1) == 'R')&&(*(i+2)=='U')&&(*(i+3)=='E')) i+=3;
			else if ((*i == 'F')&&(*(i+1) == 'A')&&(*(i+2)=='L')&&(*(i+3)=='S')&&(*(i+4)=='E'))i+=4;
		}
		//If we have a function, it must be of form Der(...) and it must either be a built in function
		//or it must be in a function list in a local text file called "Equation_Solver_Functions.txt".
		//After conducting the function search, built in functions will be prepended with a "#".
		//and user defined functions will be prepended with a "$".
		else if(std::isupper(*i) && std::islower(*(i+1)))
		{

		}
		//If we have a constant, it must consist of all uppercase letters and it must not be a reserved boolean logic word.
		//User defined constants can hold a value. Their value can be held in "Equation_Solver_Constants.txt"
		//User defined constants that have a value will be given a double quotation mark as a prefix.
		//User defined constants without a pre-listed value will have a single quotation mark prefix.
		//Check for clashes with matrixes defined in "Equation_Solver_Matrixes". Matrixes must be all uppercase too.
		//User defined matrixes must always have an assigned value {with braces} and will be given the prefix "\".
		//Post inspection, all user defined constants will be prepended with an &.
		//All boolean logic functions will be prepended by a "_".
		//TRUE and FALSE will be preceded by a "|".
		else if(std::isupper(*i) && !(std::islower(*(i+1))) )
		{

		}
	}
	return 0;
}

