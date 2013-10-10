/*! \file Equation_Solver.h
    \brief File Equation_Solver.h contains the declarations of all structs, namespaces, and functions that make up the equation solver.

    This program inputs an equation as a string of alphanumeric characters and then outputs the solution to the equation.
    Equations consist of: variables expressed as lowercase letters, constants expressed as uppercase letters, numbers expressed in base 10, unary operators, binary operators, and parenthesis.
*/

/*
 This file, Equation_Solver.h is part of the Equation_Solver source.

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

#ifndef EQUATION_SOLVER_H_
#define EQUATION_SOLVER_H_
#include <iostream>
using namespace std;
// Note: characters get converted to a 128bit-padded-long-double via std::stold.

/**
 * A matrix class. Only valid for matrixes with less than seven dimensions that contain 128bit or infinite percision decimals, 64-bit of infinite percision integers, 128-bit mixed numbers, and 256-bit imaginary numbers of form (a + b*i).
 */
class matrix {};

/**
 * A vector class. Only valid for vectors with less than six dimensions that contain 128-bit or infinite percision decimals, 64-bit of infinite percision integers, 128-bit mixed numbers, and 256-bit imaginary numbers of form (a + b*i).
 */
class vector: public matrix {};

/**
 * A 128-bit mixed number class. Consists of a 64 bit numerator and a 64 bit denominator.
 */
class mixed_number {};

/**
 * A 256-bit imaginary number (a + b*i). Consists of an 80 bit long double value for a and an 80 bit long double value for b.
 */
class imaginary_number {};

/**
* The parenthesize function checks and adds parenthesis or breaks up the expression based on order of operations.
* @param equation The equation that goes into the parenthesizer.
* @return The equation with extra parenthesis set up to explicitly define order of computation.
*/
string parenthesize(string equation);

/**
* The simplify function breaks down an equation by simplifying the expression in the innermost parenthesis. It determines whether an expression is binary orunary and then hands the job to the binary or unary simplify functions.
* @param equation The equation that goes into the parser.
* @return The equation with innermost parenthesis expression simplified.
*/
string simplify(string equation);

namespace binary
{
	/**
	* The binary::simplify function simplifies a binary expression. It examines a string containing a binary operator and then hands the actual computation of the expression to the appropriate operator function.
	* @param binary_expression A string containing one operator and two expressions on opposite sides of the operator.
	* @return The result of computing the binary operation.
	*/
	string simplify(string binary_expression);

	/**
	* The binary::add function evaluates a binary expression that contains the "+" operator".
	* @param binary_expression A string containing the add operator and an expression on either side of that operator.
	* @return The sum of the values in the binary expression.
	*/
	string add(string binary_expression);

	/**
	* The binary::subtract function evaluates a binary expression that contains the "-" operator.
	* @param binary_expression A string containing the subtract operator and an expression on either side of that operator.
	* @return The subtraction of the values in the binary expression.
	*/
	string subtract(string binary_expression);

	/**
	* The binary::multiply function evaluates a binary expression that contains the "*" operator.
	* @param binary_expression A string containing the multiply operator and an expression on either side of that operator.
	* @return The subtraction of the values in the binary expression.
	*/
	string multiply(string binary_expression);

	/**
	* The binary::divide function evaluates a binary expression that contains the "/" operator.
	* @param binary_expression A string containing the divide operator and an expression on either side of that operator.
	* @return The subtraction of the values in the binary expression.
	*/
	string divide(string binary_expression);

	/**
	* The binary::log function evaluates a binary expression that contains the "log" operator.
	* @param binary_expression A string containing the log operator and an expression on either side of that operator.
	* @return The log of the first expression with the base of the second expression.
	*/
	string divide(string binary_expression);

	/**
	* The binary::exponentiate function evaluates a binary expression that contains the "expo" operator.
	* @param binary_expression A string containing the expo operator and an expression on either side of that operator.
	* @return The first expression to the power of the second expression.
	*/
	string divide(string binary_expression);

	/**
	* The binary::derive function computes the derivative of a derivable multi-variable expression with respect to a specified variable. If the given variable is replaced with a number, say n,the unary derivative of the expression will be taken n times.
	* Note: A binary expression in the form "(x^2 + y^2) der 3" will throw an error because the computer does not know which variable to take the third derivative with respect to.
	* @param binary_expression A mathematical expression containing a derivable expression, the der operator, and the variable whom we will be taking the derivative with respect to (or the number of times the derivative will be taken), in that order.
	* @return The result produced by taking the derivative of the multivariable expression with respect to the given variable or the result of taking the derivative with respect to one variable n times.
	*/
	string derive(string binary_expression);

	/**
	* The binary::antiderive function is designed to compute the antiderivative of a multi-variable integratable expression with respect to a specified variable. If the given variable is replaced with a number n, the unary antiderivative of the expression will be taken n times.
	* Note: A binary expression in the form "(x^2 + y^2) antider n" will throw an error because the computer does not know which variable to take the nth antiderivative with respect to.
	* @param binary_expression A mathematical expression containing an integratable expression, the antider operator, and the variable whom we will be taking the derivative with respect to (or the number of times the antiderivative will be taken), in that order.
	* @return The result produced by taking the antiderivative of the expression with respect to the variable in it.
	*/
	string antiderive(string unary_expression);
}

namespace unary
{
	/**
	* The unary::simplify function simplifies a unary expression. It examines a string containing the unary operator and then hands the actual computation of the expression to the appropriate operator function.
	* @param unary_expression A string containing one mathematical operator and one expression.
	* @return The value result of computing the unary operation.
	*/
	string simplify(string unary_expression);

	/**
	* The unary::derive function computes the derivative of a derivable expression.
	* @param unary_expression A mathematical expression containing a preceding der operator and a derivable expression.
	* @return The result produced by taking the derivative of the expression with respect to each variable in it.
	*/
	string derive(string unary_expression);

	/**
	* The unary::antiderive function computes the antiderivative of an integratable expression that contains one variable.
	* The unary antiderive function throw an error if the expression contains multiple variables (which are expressed as lowercase letters). To integrate with respect to a particular variable, use the binary antiderive function.
	* @param unary_expression A mathematical expression containing a preceding antider operator and a derivable expression.
	* @return The result produced by taking the antiderivative of the expression with respect to the variable in it.
	*/
	string antiderive(string unary_expression);

	/**
	* The unary::negate function negates a T/F value (True or False value) and also flips the sign of a number.
	* @param unary_expression a boolean or numerical value preceded by a "-" operator.
	* @return The negated expression as a string.
	*/
	string negate(string unary_expression);

	/**
	* The unary::get_factorial function gets the product of all positive integers less than or equal to n.
	* Note: If you call get_factorial on a decimal that is further than .01 away from the nearest integer, an invalid input expression will be thrown. Decimals that are close to their nearest integers will be rounded to that value by adding 0.5 and then rounding down.
	* @param unary_expression an integer expressor or numerical value preceded by a "!" operator.
	* @return The factoral.
	*/
	string get_factorial(string unary_expression);
}

#endif /* EQUATION_SOLVER_H_ */
