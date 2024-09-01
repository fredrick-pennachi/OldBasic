#include "DimCommand.h"

#include "ValueNode.h"

#include <sstream>

const std::string DimCommand::DIM_COMMAND_NAME = "DIM";

DimCommand::DimCommand(
	const std::vector<Lexeme>& lexemes,
	std::string arrayName,
	std::unique_ptr<ExpressionNode> expression)
	: Command(DIM_COMMAND_NAME, lexemes), arrayName(arrayName), expression(move(expression))
{
}

/*

Forms of DIM:

DIM A(10)
DIM A(I)
DIM A(I + 1)

*/

int DimCommand::invoke()
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

	Value arraySize = expression->eval();

	if (arraySize.getType() == INTEGER) {

		runtime.setVariable(arrayName, arraySize);
	}
	else {
		throw InvalidSyntaxException("DIM expression must evaluate to an INTEGER value!");
	}

	return 0;
}

