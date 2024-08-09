#include "LetCommand.h"
#include "ValueNode.h"

#include <sstream>

const std::string LetCommand::LET_COMMAND_NAME = "LET";

LetCommand::LetCommand(
	const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(LET_COMMAND_NAME, lexemes), expression(move(expression))
{
}

/*

Forms of LET:

LET A = 1
LET B$ = "B"
LET A = A + 1

*/

int LetCommand::invoke()
{
	if (expression->nodeType == ExpressionNode::NULL_NODE) {
		// No expression, print all the variables.
		std::map<std::string, Value>::const_iterator iter = runtime.variables.cbegin();

		runtime << "Variables:" << std::endl;

		for (; iter != runtime.variables.cend(); iter++)
		{
			runtime << iter->first << ": " << iter->second << std::endl;
		}

		return 0;
	}

	Value value = expression->eval();

	if (value.isVariable()) {
		runtime.setVariable(value.var.name, value);
	}
	else {
		std::stringstream ss;
		ss << (*this);
		throw InvalidSyntaxException("Unsupported assignment: \"" + ss.str() + "\"");
	}

	return 0;
}

