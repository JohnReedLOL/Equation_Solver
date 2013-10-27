/*! \file main.cpp
    \brief File main.cpp contains the main method of the Equation_Solver program.

    Main is responsible for user input and output and calling the functions defined in Equation_Solver.cpp .
*/

/*
 This file, main.cpp is part of the Equation_Solver source.

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
using namespace std;

static inline bool exists_test (const std::string& name) {
   if (FILE *file = std::fopen(name.c_str(), "r")) {
       std::fclose(file);
       return true;
   } else {
       return false;
   }
}

int main(int argc, char **argv)
{
	std::puts("Welcome to Equation_Solver.");
	FILE *file_ptr;

	if(exists_test("Equation_Solver_Instructions.txt"))
	{
		//Assume it has all the constants already inside.
	}
	else
	{
		file_ptr = std::fopen("Equation_Solver_Instructions.txt", "w");
		fputs("Welcome to Equation_Solver. \n\n",file_ptr);
		fputs("Before you begin writing mathematical equations and expressions, you need to know the four rules:\n",file_ptr);
		fputs("#1. All variables are composed entirely of lowercase letters with an optional number at the end.\n",file_ptr);
		fputs("x, x1, y, y1, z, and z1 are all legal variables. \n\n",file_ptr);
		fputs("#2. All functions must consist of one uppercase letter followed by all lowercase letters followed by parenthesis. \n",file_ptr);
		fputs("Der(x^2) and Log(8,2) are both legal functions. \n\n",file_ptr);
		fputs("#3. All constants must consist entirely of uppercase letters. \n",file_ptr);
		fputs("PI, E(the natural number), and I(the imaginary number) are all legal constants. \n",file_ptr);
		fputs("For the list of legal functions, see the file Equation_Solver_Functions.txt in the Equation_Solver folder\n\n",file_ptr);
		fputs("#4. There are eight and only eight boolean tokens. \n",file_ptr);
		fputs("They are: AND OR XOR IF IFF NOT TRUE and FALSE \n", file_ptr);
		fputs("So TRUE AND FALSE makes FALSE, but TRUE OR FALSE makes TRUE. \n\n", file_ptr);

		fputs("Now all you have to do is run the Equation_Solver and put together the legal functions with the '+ - * / % ^ () < > =' operators to make solvable equations!\n\n",file_ptr);
		std::fclose(file_ptr);
	}

	if(exists_test("Equation_Solver_Functions.txt"))
	{
		//Assume it has all the functions already inside.
	}
	else
	{
		file_ptr = std::fopen("Equation_Solver_Functions.txt", "w");
		fputs("This file contains your functions for Equation_Solver \n",file_ptr);
		fputs("Functions must start with an uppercase letter and then have some lowercase letters followed by a set of parenthesis.\n",file_ptr);
		fputs("For example: \n\n",file_ptr);
		fputs("Log(x,b) = The log of 'x' base 'b'. \n",file_ptr);
		fputs("Base(x,b) = The value of 'x' expressed in base 'b'. If b is 2 you get binary. \n\n",file_ptr);
		fputs("Fact(x) = x factorial, or x!. It equal x*(x-1)*(x-2)*...*(1)",file_ptr);

		fputs("Der(equation) = The derivative of 'equation' with respect to the only variable in the equation.  \n",file_ptr);
		fputs("Der(equation,C) = The derivative of 'equation' at constant 'C'.  \n",file_ptr);
		fputs("Der(equation,x) = The partial derivative of 'equation' with respect to the variable 'x'. \n",file_ptr);
		fputs("Der(equation,x,C) = The partial derivative of 'equation' with respect to 'x' where x=C.  \n\n",file_ptr);

		fputs("Int(equation) = The integral of 'equation' with respect to the only variable in the equation.  \n",file_ptr);
		fputs("Int(equation,C) = The integral of 'equation' at constant 'C'.  \n",file_ptr);
		fputs("Int(equation,C,D) = The area under the curve from 'C' to 'D'.  \n",file_ptr);
		fputs("Int(equation,x) = The partial derivative of 'equation' with respect to the variable 'x'. \n",file_ptr);
		fputs("Int(equation,x,C) = The integral of 'equation' with respect to 'x' at x = 'C'.  \n",file_ptr);
		fputs("Int(equation,x,C,D) = The area under the curve from 'C' to 'D'. \n\n",file_ptr);

		fputs("Sin(theta) = the trigonometric Sin function \n",file_ptr);
		fputs("Cos(thera) = the trigonometric Cosine function \n",file_ptr);
		fputs("Tan(theta) = Sin(theta)/Cos(theta) \n",file_ptr);
		fputs("Cosec(theta) = 1/Sin(theta) \n",file_ptr);
		fputs("Sec(theta) = 1/Cos(theta) \n",file_ptr);
		fputs("Cotan(theta) = Cos(theta)/Sin(theta) \n",file_ptr);
		fputs("Arctan(theta) = the inverse of Sin \n",file_ptr);
		fputs("Arccos(theta) = the inverse of Cos \n",file_ptr);
		fputs("Arctan(theta) = the inverse of Tan \n",file_ptr);

		fputs("\nYou can create your own functions below: \n",file_ptr);
		std::fclose(file_ptr);
	}

	if(exists_test("Equation_Solver_Constants.txt"))
	{
		//Assume it has all the constants already inside.
	}
	else
	{
		file_ptr = std::fopen("Equation_Solver_Constants.txt", "w");
		fputs("This file contains your constants for Equation_Solver \n",file_ptr);
		fputs("Constants must be in all caps. Each constant must be set equal to something.\n",file_ptr);
		fputs("Only one constant per line allowed.",file_ptr);
		fputs("For example: \n",file_ptr);
		fputs("PI = 3.141592653589793238462643 \n",file_ptr);
		fputs("E = 2.718281828459045235360287 \n",file_ptr);
		fputs("I = (-1)^(1/2) \n",file_ptr);
		fputs("\nYou can create your own constants below: \n",file_ptr);
		std::fclose(file_ptr);
	}

	if(exists_test("Equation_Solver_Constants.txt"))
	{
		//Assume it has all the constants already inside.
	}
	else
	{
		file_ptr = std::fopen("Equation_Solver_Booleans.txt", "w");
		fputs("This file tells you what the built in boolean logic functions are \n",file_ptr);
		fputs("The eight tokens are: \n",file_ptr);
		fputs("AND \n",file_ptr);
		fputs("OR (inclusive or) \n",file_ptr);
		fputs("XOR (exclusive or) \n",file_ptr);
		fputs("IF ('a IF b' is the same as 'if b is true, then a is true'. Note the reversal of a and b.) \n",file_ptr);
		fputs("IFF (if and only if) \n",file_ptr);
		fputs("NOT \n",file_ptr);
		fputs("TRUE \n",file_ptr);
		fputs("FALSE \n",file_ptr);
		fputs("\nNote that you only get these 8 boolean tokens. You can't make more.  \n",file_ptr);
		std::fclose(file_ptr);
	}
	std::puts("If this is your first time using this program, make sure to look in my current folder for the instructions.");
	char equation[23000];
	std::puts("After you've looked at the instructions, write an equation using the symbols +, -, *, /, %, ^, (,), <, >, and =. ");
	std::cin.getline (equation,15006);
	const int string_Length = std::cin.gcount();
	if( string_Length > 10000)
	{
		std::puts("You are approaching the 15000 character limit.");
	}
	if( string_Length > 15000)
	{
		std::puts("You just went over the 15000 character limit. Equation_Solver terminating.");
		return 1;
	}
	else // 6 null terminating null characters at the end.
	{
		equation[string_Length] = '\0';
		equation[string_Length+1] = '\0';
		equation[string_Length+2] = '\0';
		equation[string_Length+3] = '\0';
		equation[string_Length+4] = '\0';
		equation[string_Length+5] = '\0';
	}
	if (::parenthesize(equation) == nullptr)
	{
		std::puts("Closing program due to error");
		return 1;
	}
	return 0;
}


