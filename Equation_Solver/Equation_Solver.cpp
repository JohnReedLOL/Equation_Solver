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

char * parenthesize(char * equation)
{

	int counter = 0;
	for (char * i = equation; *i != '\0'; ++i)
	{
		if (*i == '{')
			++counter;
		else if (*i = '}')
			--counter;
	}
	char error[1] = '\0';
	char * error_ptr = error;
	if (counter != 0)
		return error_ptr;

	char * open_paren_ptr = 0;
	char * closed_paren_ptr = 0;

	char * i;
	for (i = equation; (*i != ')') && (*i != '\0'); ++i)
	{
		if (*i == '(')
			open_paren_ptr = i;
	}

	if (*i == ')')
	{
		closed_paren_ptr = i;
	}
	else //*i == '\0'
	{
		i = equation;
	}
//Now look to see which operators are between the parenthesis
//Or if no parenthesis, take the first operator and assume left to right order of operations.

}

