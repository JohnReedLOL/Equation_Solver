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


enum Type { begin, open, closed, plusOrMinus, binaryOp, unaryOp, binaryWord
                 , unaryWord, constant, variable, function, bliteral, intliteral, decliteral, end };

struct Begin {
//Begin marks the end of the vector of tokens. For example, " *3 " = " Start*3 ", which would be invalid.	
};

struct Open {
	char * name;
};

struct Closed {
	char * name;
};

struct PlusOrMinus {
	char * name;
	int numOperands;
};

//Note: Comma and semicolon are binary ops
struct BinaryOp {
	char * name;
};

struct UnaryOp {
	char * name;
};

struct BinaryWord {
	char * nameBeg;
	//char * nameEnd; - Words will be null terminated
};

struct UnaryWord {
	char * nameBeg;
	//char * nameEnd; - Words will be null terminated
};

struct Constant {
	// Constants will point to their origional definition in Equation_Solver_Constants
	//or in the input line.
	// Undefined constants will have a nullptr definition.
	char * nameBeg;
	char * nameEnd;
	char * defBegin;
	char * defEnd;
};

struct Variable {
	// Variables will point to their origional definition
	//in the input line.
	// Undefined variables will have a nullptr definition.
	char * nameBeg;
	char * nameEnd;
	char * defBegin;
	char * defEnd;
};

struct Function {
	// Functions will point to their origional definition in Equation_Solver_Functions
	//or in the input line.
	// Undefined functions cannot exist because functions cannot be defined during runtime.
	char * nameBeg;
	char * nameEnd;
	char * defBegin;
	char * defEnd;
};

//Will use a plain bool in the template instead.
struct BLit {
	bool val;
	//Name unnecessary because bool val can be printed.
	//char * nameBeg; // = "TRUE" or "FALSE" null terminated.
	//char * nameEnd; - not necesary
};

struct BInt {
	long num;
	long denom;
	long inum;
	long idenom;
	//char * nameBeg;
	//char * nameEnd;
};

struct BDec {
	long double dec;
	long double idec;
	//char * nameBeg;
	//char * nameEnd;
};

struct End {
//End marks the end of the vector of tokens. For example, "1+2+" = "1+2+End", which is invalid.	
};

struct token {
	Type myType;
	union {
    	Open 		myOpen;
    	Closed 		myClosed;
    	PlusOrMinus 	myPlusOrMinus;
    	BinaryOp 	myBinaryOp;
    	UnaryOp 	myUnaryOp;
    	BinaryWord 	myBinaryWord;
    	UnaryWord 	myUnaryWord;
    	Constant 	myConstant;
    	Variable	myVariable;
    	Function	myFunction;
    	BLit		myBLit;
    	BInt		myBInt;
    	BDec		myBDec;
  	};
}

char * parenthesize(std::string equation) {
	int counter1 = 0;
	int counter2 = 0;
	int counter3 = 0;
	int counter4 = 0;
	int counter5 = 0;
	int counter6 = 0;

	bool reachedEquals = false;
	int counter1left = 0;
	int counter1right = 0;
	int counter2left = 0;
	int counter2right = 0;
	int counter3left = 0;
	int counter3right = 0;

	//Max 1 line per equation. NO SUPPORT YET FOR COMMA OR SEMICOLON.
	for (char * i = equation;
			(*i != '\0') && (*i != (char) 10) && (*i != (char) 13); ++i) {
		if (((int) (*i)) < 32 || ((int) (*i)) > 125 || *i == '!'
				|| ((int) (*i)) == 34 || *i == '#' || *i == '$' || *i == '&'
				|| ((int) (*i)) == 39 || *i == ':' || *i == '?' || *i == '@'
				|| ((int) (*i)) == 92 || *i == '_' || ((int) (*i)) == 96
				|| *i == '|') {
			std::cerr << "Error! I do not understand the \"" << (*i)
					<< "\" symbol." << std::endl;
			return nullptr;
		}

		bool isBinary1 = false;
		bool isBinaryWord1 = false;
		bool isOpen1 = false;

		bool isConstant1 = false;
		bool isVariable1 = false;
		bool isFunction1 = false;
		
		bool BLit1 = false;
		bool BDec1 = false;
		bool BInt1 = false;

		bool isBinary2 = false;
		bool isBinaryWord2 = false;
		bool isClosed2 = false;

		bool isConstant2 = false;
		bool isVariable2 = false;
		bool isFunction2 = false;
		bool BLit2 = false;
		bool BDec2 = false;
		bool BInt2 = false;

		bool isPlusMinus1 = false;
		bool isPlusMinus2 = false;

		std::tuple<std::string> equation_tuple ("START");

		//auto first = std::make_tuple (10,'a');

		//std::tuple <std::string> mytuple ("START");

		//perhaps add a space to the end of tokens.
		//(*(i+9)=='\0')&&(*(i+9)==(char)10)&&(*(i+9)==(char)13)&&(*(i+9)==(char)32)
		// TRUE ANDOVER = TRUE AND OVER - assumes OVER is a boolean. FALSE AND.

		if ((std::islower(*i))) {
			isVariable1 = true;
			char * start = i;

			++i;
			for (;
					*i != ' ' && *i != '+' && *i != '-' && *i != '*'
							&& *i != '/' && *i != '%' && *i != '!' && *i != '^'
							&& *i != '(' && *i != ')' && *i != '[' && *i != ']'
							&& *i != '{' && *i != '}' && *i != ';' && *i != '<'
							&& *i != '>' && *i != '=' && *i != ','
							
							&& !((*i == 'A') && (*(i + 1) == 'N') && (*(i + 2) == 'D') && (*(i + 3) == ' '))
							
							&& !((*i == 'O') && (*(i + 1) == 'R') && (*(i + 2) == ' '))
							
							&& !((*i == 'X') && (*(i + 1) == 'O' ) && (*(i + 2) == 'R') && (*(i + 3) == ' '))
							
							&& !((*i == 'N') && (*(i + 1) == 'O') && (*(i + 2) == 'T') && (*(i + 3) == ' '))
							
							&& !((*i == 'I') && (*(i + 1) == 'F')&& (*(i + 2) == ' '))
							
							&& !((*i == 'I') && (*(i + 1) == 'F') && (*(i + 2) == 'F') && (*(i + 3) == ' '))
							
							&& !((*i == 'T') && (*(i + 1) == 'R') && (*(i + 2) == 'U') && (*(i + 3) == 'E') && (*(i + 4) == ' '))
							
							&& !((*i == 'F') && (*(i + 1) == 'A')&& (*(i + 2) == 'L') && (*(i + 3) == 'S')&& (*(i + 4) == 'E') && (*(i + 5) == ' ')); ++i) {
				if (std::isupper(*i)) {
					std::cerr
							<< "Variable names must start with a lowercase letter and cannot contain uppercase letters."
							<< std::endl;
					return nullptr;
				} else if (std::isdigit(*i)) {
					if (std::islower(*(i + 1))) {
						std::cerr
								<< "Numbers can only go at the very end of variable names."
								<< std::endl;
						return nullptr;
					}
				}
			}
			char * onePastEnd = i;
			std::string name = 
		} else if (std::isupper(*i) && std::islower(*(i + 1))) {
			//AN UPPER FOLLOWED BY A LOWER COULD ALSO BE IN FORM: "Ax1 + Bx2 = 7 - Ax1"
			// Solution: 2Ax1 + Bx2 - 7 = 0;
			isFunction1 = true;
			++i;
			while (true ) {
				if (*i == '(') {
					char * functionOpenPtr = i;
					while(*i != ')')
					{
						++i;
					}
					char * functionClosedPtr = i;
					//CREATE A FUNCTION STRUCT WITH DEFINITION BETWEEN THE TWO PTRS!!!.
					break;
				} else if (*i == ' ' || *i == '+' || *i == '-' || *i == '*' || *i == '/'
						|| *i == '%' || *i == '^' || *i == ')'
						|| *i == '[' || *i == ']' || *i == '{' || *i == '}'
						|| *i == ';' || *i == '<' || *i == '>' || *i == '='
						|| *i == ',' || (isupper(*i)) || (::isdigit(*i))) {
					std::cerr
							<< "Error! Functions must consist of a capital letter followed by lowercase letters followed by parenthesis."
							<< std::endl;

					return nullptr;
				}
				//Else increment to the next lowercase character.
				++i;
			}
		} else if (*i == '*' || *i == '/' || *i == '%' || *i == '^' || *i == '+'
				|| *i == '-' || *i == '<' || *i == '>' || *i == '=') {
			++i;
			isBinary1 = true;
			if (*i == '+' || *i == '-')
				isPlusMinus1 = true;

		} else if (((*i == 'I') && (*(i + 1) == 'F'))) {
			i += 2;
			isBinaryWord1 = true;
		} else if (((*i == 'O') && (*(i + 1) == 'R'))) {
			i += 2;
			isBinaryWord1 = true;
		} else if (((*i == 'A') && (*(i + 1) == 'N') && (*(i + 2) == 'D'))) {
			i += 3;
			isBinaryWord1 = true;
		} else if (((*i == 'X') && (*(i + 1) == 'O') && (*(i + 2) == 'R'))) {
			i += 3;
			isBinaryWord1 = true;
		} else if (((*i == 'N') && (*(i + 1) == 'O') && (*(i + 2) == 'T'))) {
			i += 3;
			isBinaryWord1 = true;
		} else if (((*i == 'I') && (*(i + 1) == 'F') && (*(i + 1) == 'F'))) {
			i += 3;
			isBinaryWord1 = true;
		} else if (((*i == 'T') && (*(i + 1) == 'R') && (*(i + 2) == 'U')
				&& (*(i + 3) == 'E'))) {
			i += 4;
			isBinaryWord1 = true;
		} else if (((*i == 'F') && (*(i + 1) == 'A') && (*(i + 2) == 'L')
				&& (*(i + 3) == 'S') && (*(i + 4) == 'E'))) {
			i += 5;
			isBinaryWord1 = true;
		} else if (*i == '(' || *i == '[' || *i == '{') {
			++i;
			isOpen1 = true;
		} else if (std::isupper(*i)) {
			isConstant1 = true;
			++i;
			while (*i != ' ' && *i != '+' && *i != '-' && *i != '*' && *i != '/'
					&& *i != '%' && *i != '!' && *i != '^' && *i != ')'
					&& *i != ')' && *i != '[' && *i != ']' && *i != '{'
					&& *i != '}' && *i != ';' && *i != '<' && *i != '>'
					&& *i != '=' && *i != ',' && !(islower(*i))) {
				++i;
				if (std::isdigit(*i)) {
					if (std::isupper(*(i + 1))) {
						std::cerr
								<< "Numbers can only go at the very end of a constant."
								<< std::endl;
						return nullptr;
					}
				}
			}
			//Else increment to the next lowercase character.
		}

		//ignore whitespace between words.
		while (*i == ' ') {
			++i;
		}

		if (*i == '*' || *i == '/' || *i == '%' || *i == '^' || *i == '<'
				|| *i == '>' || *i == '=') {
			++i;
			isBinary2 = true;
			if (*i == '+' || *i == '-')
				isPlusMinus2 = true;
		} else if (((*i == 'I') && (*(i + 1) == 'F'))) {
			i += 2;
			isBinaryWord2 = true;
		} else if (((*i == 'O') && (*(i + 1) == 'R'))) {
			i += 2;
			isBinaryWord2 = true;
		} else if (((*i == 'A') && (*(i + 1) == 'N') && (*(i + 2) == 'D'))) {
			i += 3;
			isBinaryWord2 = true;
		} else if (((*i == 'X') && (*(i + 1) == 'O') && (*(i + 2) == 'R'))) {
			i += 3;
			isBinaryWord2 = true;
		} else if (((*i == 'N') && (*(i + 1) == 'O') && (*(i + 2) == 'T'))) {
			i += 3;
			isBinaryWord2 = true;
		} else if (((*i == 'I') && (*(i + 1) == 'F') && (*(i + 1) == 'F'))) {
			i += 3;
			isBinaryWord2 = true;
		} else if (((*i == 'T') && (*(i + 1) == 'R') && (*(i + 2) == 'U')
				&& (*(i + 3) == 'E'))) {
			i += 4;
			isBinaryWord2 = true;
		} else if (((*i == 'F') && (*(i + 1) == 'A') && (*(i + 2) == 'L')
				&& (*(i + 3) == 'S') && (*(i + 4) == 'E'))) {
			i += 5;
			isBinaryWord2 = true;
		} else if (*i == ')' || *i == ']' || *i == '}') {
			isClosed2 = true;
		}

		if ((isBinary1 && isBinary2) || (isBinary1 && isClosed2)
				|| (isOpen1 && isBinary2)) {
			std::cerr << "Error! You cannot have a \"" << *i
					<< "\" followed by a \"" << *(i + 1) << "\".\n"
					<< std::endl;
			return nullptr;
		} else if ((isBinaryWord1 && isBinary2) || (isBinary1 && isBinaryWord2)
				|| (isBinaryWord1 && isClosed2) || (isOpen1 && isBinaryWord2)) {
			std::cerr
					<< "Error! A boolean operator is clashing with some other operator or with some parenthesis/brackets/braces."
					<< std::endl;
			return nullptr;
		}

		if (*i == '{') {
			++counter1;
			if (reachedEquals == false)
				++counter1left;
			else
				++counter1right;
		} else if (*i == '}') {
			--counter1;
			if (reachedEquals == false)
				--counter1left;
			else
				--counter1right;
		}

		if (*i == '(') {
			++counter2;
			if (reachedEquals == false)
				++counter2left;
			else
				++counter2right;
		} else if (*i == ')') {
			--counter2;
			if (reachedEquals == false)
				--counter2left;
			else
				--counter2right;
		}

		if (*i == '[') {
			++counter3;
			if (reachedEquals == false)
				++counter3left;
			else
				++counter3right;
		} else if (*i == ']') {
			--counter3;
			if (reachedEquals == false)
				--counter3left;
			else
				--counter3right;
		}

		if (*i == '=') {
			++counter4;
			reachedEquals = true;
		} else if (*i == '>') {
			++counter5;
			reachedEquals = true;
		} else if (*i == '<') {
			++counter6;
			reachedEquals = true;
		}
	}

	if (counter1 != 0 || counter1left != 0 || counter1right != 0) {
		if (counter1 > 0)
			std::cerr << "Error! More open braces than closed braces. \n"
					<< std::endl;
		else if (counter1left > 0)
			std::cerr
					<< "Error! More open braces than closed braces on the left side of the equation or inequality.\n"
					<< std::endl;
		else if (counter1right > 0)
			std::cerr
					<< "Error! More open braces than closed braces on the right side of the equation or inequality.\n"
					<< std::endl;
		else if (counter1 < 0)
			std::cerr << "Error! More closed braces than closed braces. \n"
					<< std::endl;
		else if (counter1left < 0)
			std::cerr
					<< "Error! More closed braces than open braces on the left side of the equation or inequality.\n"
					<< std::endl;
		else if (counter1right < 0)
			std::cerr
					<< "Error! More closed braces than open braces on the right side of the equation or inequality.\n"
					<< std::endl;
		return nullptr;
	} else if (counter2 != 0 || counter2left != 0 || counter2right != 0) {
		if (counter2 > 0)
			std::cerr
					<< "Error! More open parentheses than closed parentheses. \n"
					<< std::endl;
		else if (counter2left > 0)
			std::cerr
					<< "Error! More open parentheses than closed parentheses on the left side of the equation or inequality.\n"
					<< std::endl;
		else if (counter2right > 0)
			std::cerr
					<< "Error! More open parentheses than closed parentheses on the right side of the equation or inequality.\n"
					<< std::endl;
		else if (counter2 < 0)
			std::cerr
					<< "Error! More closed parentheses than closed parentheses. \n"
					<< std::endl;
		else if (counter2left < 0)
			std::cerr
					<< "Error! More closed parentheses than open parentheses on the left side of the equation or inequality.\n"
					<< std::endl;
		else if (counter2right < 0)
			std::cerr
					<< "Error! More closed parentheses than open parentheses on the right side of the equation or inequality.\n"
					<< std::endl;
		return nullptr;
	} else if (counter3 != 0 || counter3left != 0 || counter3right != 0) {
		if (counter3 > 0)
			std::cerr << "Error! More open brackets than closed brackets. \n"
					<< std::endl;
		else if (counter3left > 0)
			std::cerr
					<< "Error! More open brackets than closed brackets on the left side of the equation or inequality.\n"
					<< std::endl;
		else if (counter3right > 0)
			std::cerr
					<< "Error! More open brackets than closed brackets on the right side of the equation or inequality.\n"
					<< std::endl;
		else if (counter3 < 0)
			std::cerr << "Error! More closed brackets than closed brackets. \n"
					<< std::endl;
		else if (counter3left < 0)
			std::cerr
					<< "Error! More closed brackets than open brackets on the left side of the equation or inequality.\n"
					<< std::endl;
		else if (counter3right < 0)
			std::cerr
					<< "Error! More closed brackets than open brackets on the right side of the equation or inequality.\n"
					<< std::endl;
		return nullptr;
	} else if (counter4 > 1) {
		std::cerr << "Error! Too many \"=\" signs. " << std::endl;
		return nullptr;
	} else if (counter5 > 1) {
		std::cerr << "Error! Too many \">\" signs. " << std::endl;
		return nullptr;
	} else if (counter6 > 1) {
		std::cerr << "Error! Too many \"<\" signs. " << std::endl;
		return nullptr;
	} else if ((counter4 > 0 && counter5 > 0)
			|| (counter6 > 0 && counter4 > 0)) {
		std::cerr
				<< "Error! The greater than or equal to sign is not supported. "
				<< std::endl;
		return nullptr;
	} else if (counter6 > 0 && counter5 > 0) {
		std::cerr
				<< "Error! You're got a mixture of both \">\" and \"<\" signs in the same equation. "
				<< std::endl;
		return nullptr;
	}

	char * open_paren_ptr = nullptr;
	char * closed_paren_ptr = nullptr;

	char * i;
	for (i = equation;
			(*i != ')') && (*i != '\0') && (*i != (char) 10)
					&& (*i != (char) 13) && (*i != '='); ++i) {
		if (*i == '(')
			open_paren_ptr = i;
	}

	if (*i == ')') {
		closed_paren_ptr = i;
		if (open_paren_ptr == nullptr) {
			std::cerr << "You misplaced your open parenthesis." << std::endl;
			return nullptr;
		} else {
			i = open_paren_ptr;
		}
	} else if (*i == '=') {
		closed_paren_ptr = i;

		if (open_paren_ptr == nullptr) {
			open_paren_ptr = equation;
			i = open_paren_ptr;
		} else {
			i = open_paren_ptr;
		}
	} else if (*i == '\0' || (*i != (char) 10) || (*i != (char) 13)) {
		closed_paren_ptr = i;

		if (open_paren_ptr == nullptr) {
			open_paren_ptr = equation;
			i = open_paren_ptr;
		} else {
			std::cerr
					<< "Error! Reached the end of input, but have unclosed parenthesis."
					<< std::endl;
			return nullptr;
		}
	}

	char * open_bracket_ptr = nullptr;
	char * closed_bracket_ptr = nullptr;

	char * j;
	for (j = equation;
			(*j != ']') && (*j != '\0') && (*j != (char) 10)
					&& (*j != (char) 13) && (*j != '='); ++j) {
		if (*j == '[')
			open_bracket_ptr = j;
	}

	if (*j == ']') {
		closed_bracket_ptr = j;
		if (open_bracket_ptr == nullptr) {
			std::cerr << "You misplaced your open parenthesis." << std::endl;
			return nullptr;
		} else {
			j = open_bracket_ptr;
		}
	} else if (*j == '=') {

		closed_bracket_ptr = j;

		if (open_bracket_ptr == nullptr) {
			open_bracket_ptr = equation;
			j = open_bracket_ptr;
		} else {
			j = open_bracket_ptr;
		}
	} else if (*j == '\0' || (*j != (char) 10) || (*j != (char) 13)) {
		closed_bracket_ptr = j;

		if (open_bracket_ptr == nullptr) {
			open_bracket_ptr = equation;
			j = open_bracket_ptr;
		} else {
			std::cerr
					<< "Error! Reached the end of input, but have unclosed brackets."
					<< std::endl;
			return nullptr;
		}
	}

	if ((open_paren_ptr < open_bracket_ptr
			&& closed_paren_ptr < closed_bracket_ptr)
			|| (open_paren_ptr > open_bracket_ptr
					&& closed_paren_ptr > closed_bracket_ptr)) {
		std::cerr << "The parenthesis and brackets are mixed up" << std::endl;
		return nullptr;
	}
//Now we have to check if there are any illegal variable, constant, or function names.

//if (0 != ::check_names(equation)) {
//	return nullptr;
//}

// Temp return. Note that it is returning an invalid address.
	static char temp = 'a';
	char * temp_ptr = &temp;
	return temp_ptr;

//Now look to see which operators are between the parenthesis
//Or if no parenthesis, take the first operator and assume left to right order of operations.

}

int check_names(char * const equation) {
	for (char * i = equation; *i != '\0'; ++i) {
		//if one letter is lowercase, it must be a variable or one of the three reserved mathematical constants e (2.71828182845904523536), pi(3.14159...), i (-1^(1/2)), or .
		//Post inspection, all variables will be prepended with a @.
		//Variables cannot be given a permanent value because then they would be constants.
		//Built in constants will be prepended with a "~".
		if ((std::islower(*i))) {
			++i;
			for (;
					*i != ' ' && *i != '+' && *i != '-' && *i != '*'
							&& *i != '/' && *i != '%' && *i != '!' && *i != '^'
							&& *i != '(' && *i != ')' && *i != '[' && *i != ']'
							&& *i != '{' && *i != '}' && *i != ';' && *i != '<'
							&& *i != '>' && *i != '=' && *i != ','
							&& !((*i == 'A') && (*(i + 1) == 'N')
									&& (*(i + 2) == 'D'))
							&& !((*i == 'O') && (*(i + 1) == 'R'))
							&& !((*i == 'X') && (*(i + 1) == 'O')
									&& (*(i + 2) == 'R'))
							&& !((*i == 'N') && (*(i + 1) == 'O')
									&& (*(i + 2) == 'T'))
							&& !((*i == 'I') && (*(i + 1) == 'F'))
							&& !((*i == 'I') && (*(i + 1) == 'F')
									&& (*(i + 1) == 'F'))
							&& !((*i == 'T') && (*(i + 1) == 'R')
									&& (*(i + 2) == 'U') && (*(i + 3) == 'E'))
							&& !((*i == 'F') && (*(i + 1) == 'A')
									&& (*(i + 2) == 'L') && (*(i + 3) == 'S')
									&& (*(i + 4) == 'E')); ++i) {
				if (std::isupper(*i)) {
					std::cerr
							<< "Variable names must start with a lowercase letter and cannot contain uppercase letters."
							<< std::endl;
					return 1;
				} else if (std::isdigit(*i)) {
					if (std::islower(*(i + 1))) {
						std::cerr
								<< "Numbers can only go at the very end of variable names."
								<< std::endl;
						return 1;
					}
				}
			}
			//Go to the end of the logical word.
			if ((*i == 'A') && (*(i + 1) == 'N') && (*(i + 2) == 'D'))
				i += 2;
			else if ((*i == 'O') && (*(i + 1) == 'R'))
				++i;
			else if ((*i == 'X') && (*(i + 1) == 'O') && (*(i + 2) == 'R'))
				i += 2;
			else if ((*i == 'N') && (*(i + 1) == 'O') && (*(i + 2) == 'T'))
				i += 2;
			else if ((*i == 'I') && (*(i + 1) == 'F'))
				++i;
			else if ((*i == 'I') && (*(i + 1) == 'F') && (*(i + 1) == 'F'))
				i += 2;
			else if ((*i == 'T') && (*(i + 1) == 'R') && (*(i + 2) == 'U')
					&& (*(i + 3) == 'E'))
				i += 3;
			else if ((*i == 'F') && (*(i + 1) == 'A') && (*(i + 2) == 'L')
					&& (*(i + 3) == 'S') && (*(i + 4) == 'E'))
				i += 4;
		}
		//If we have a function, it must be of form Der(...) and it must either be a built in function
		//or it must be in a function list in a local text file called "Equation_Solver_Functions.txt".
		//After conducting the function search, built in functions will be prepended with a "#".
		//and user defined functions will be prepended with a "$".
		else if (std::isupper(*i) && std::islower(*(i + 1))) {
			++i;
			for (;
					*i != ' ' && *i != '+' && *i != '-' && *i != '*'
							&& *i != '/' && *i != '%' && *i != '!' && *i != '^'
							&& *i != ')' && *i != '[' && *i != ']' && *i != '{'
							&& *i != '}' && *i != ';' && *i != '<' && *i != '>'
							&& *i != '=' && *i != ',' && !(isupper(*i))
							&& !(::isdigit(*i)); ++i) {
				if (*i == '(') {
					break;
				} else if (*i != '+' && *i != '-' && *i != '*' && *i != '/'
						&& *i != '%' && *i != '!' && *i != '^' && *i != ')'
						&& *i != '[' && *i != ']' && *i != '{' && *i != '}'
						&& *i != ';' && *i != '<' && *i != '>' && *i != '='
						&& *i != ',' && !(isupper(*i)) && !(::isdigit(*i))) {
					std::cerr
							<< "Error! Functions must consist of a capital letter followed by lowercase letters followed by parenthesis."
							<< std::endl;
					return 1;
				}
				//Else increment to the next lowercase character.
			}

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
		else if (std::isupper(*i)) {
			//It is a constant. Let's try to replace it with something from the list of constants.
		}
	}
	return 0;
}

