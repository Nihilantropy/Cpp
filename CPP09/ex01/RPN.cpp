#include "RPN.hpp"

RPN::RPN() {}

RPN::RPN(const RPN& other) : _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		_stack = other._stack;
	}
	return *this;
}

RPN::~RPN() {}

/* public methods */

/**
 * @brief Evaluates a Reverse Polish Notation (RPN) expression and returns the result.
 *
 * This function processes an RPN expression given as a string. The expression is 
 * split into tokens (numbers and operators), and these tokens are evaluated using 
 * a stack. The operands are pushed onto the stack, and operators perform operations 
 * on the operands by popping them off the stack, then pushing the result back onto 
 * the stack. The final result is the last remaining value in the stack.
 *
 * The function performs several checks:
 * - If the expression is empty or consists only of spaces, it throws an error.
 * - It ensures that there are at least two operands and one operator for a valid RPN expression.
 * - If there is only one operand without an operator, it throws an error.
 * - If the stack does not contain exactly one value at the end of evaluation, it throws an error.
 *
 * @param expr The RPN expression to evaluate, as a space-separated string.
 * @return The result of the evaluated expression.
 * @throws std::runtime_error If the expression is invalid (e.g., empty, invalid token, missing operator).
 */
int	RPN::evaluate(const std::string& expr)
{
	std::istringstream  iss(expr);
	std::string         token;

	while (!_stack.empty())
		_stack.pop();

	if (expr.empty() || expr.find_first_not_of(' ') == std::string::npos)
		throw std::runtime_error("Error: Empty or invalid expression");
	
	int operandCount = 0;

	while (iss >> token)
	{
		processToken(token);
		if (!isOperator(token)) {
			operandCount++;
		}
	}

	if (_stack.size() != 1)
		throw std::runtime_error("Error: Invalid RPN expression (too few operators or operands)");
	
	if (operandCount == 1)
		throw std::runtime_error("Error: Missing operator in expression");

	return _stack.top();
}

void	RPN::printResult(const std::string& expr)
{
	try {
		int	result = evaluate(expr);
		std::cout << "Result: " << result << std::endl;
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}

/**
 * @brief Processes a single token from an RPN expression.
 *
 * If the token is an operator (e.g., '+', '-', '*', '/'), it performs the operation
 * using the top two integers from the stack and pushes the result back onto the stack.
 *
 * If the token is a number, it converts the token to an integer and pushes it onto
 * the stack.
 * std::istringstream wraps the token in a stream. Use '>>' to trim the white spaces
 * around the token and to check if the token is a valid integer 
 *
 * @throws std::runtime_error for:
 * - Invalid tokens (non-operators and non-numbers).
 * - Insufficient operands on the stack when an operator is encountered.
 *
 * @param token The token to process, either a number or an operator.
 */
void	RPN::processToken(const std::string& token)
{
	if (isOperator(token))
	{
		if (_stack.size() < 2)
			throw std::runtime_error("Error: insufficient operands");

		int	b = _stack.top();
		_stack.pop();
		
		int	a = _stack.top();
		_stack.pop();

		int	result = performOperation(a, b, token);
		_stack.push(result);
	}
	else if (isValidInteger(token))
	{
		int value = atoi(token.c_str());
		_stack.push(value);
	}
	else
	{
		// Token is neither a valid operator nor an integer
		throw std::runtime_error("Error: invalid token '" + token + "'");
	}
}

bool	RPN::isValidInteger(const std::string& token) const
{
	if (token.empty())
		return false;

	size_t	start = 0;
	if (token[0] == '-')
		start = 1;

	for (size_t i = start; i < token.size(); ++i)
	{
		if (!std::isdigit(token[i]))
			return false;
	}

	return true;
}

bool	RPN::isOperator(const std::string& token) const
{
	return token == "+" || token == "-" || token == "*" || token == "/";
}

int	RPN::performOperation(int a, int b, const std::string& op)
{
	if (op == "+") return a + b;
	if (op == "-") return a - b;
	if (op == "*") return a * b;
	if (op == "/")
	{
		if (b == 0)
			throw std::runtime_error("Error: Division by zero");
		return a / b;
	}
	throw std::runtime_error("Error: unknown operator '" + op + "'");
}
