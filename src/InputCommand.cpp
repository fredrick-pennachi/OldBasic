
#include "InputCommand.h"
#include "VariableNode.h"

#include <iostream>

const std::string InputCommand::INPUT_COMMAND_NAME = "INPUT";

InputCommand::InputCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression) : Command(INPUT_COMMAND_NAME, lexemes), expression(std::move(expression))
{
}

CommandStatus InputCommand::invoke()
{
	VariableNode* varNode = dynamic_cast<VariableNode*>(expression.get());

	if (varNode == nullptr) {
		throw InvalidSyntaxException("INPUT argument must parse to a Variable!");
	}

	const std::string& varName = varNode->name;

	// Get a line of input
	runtime << "? " << std::flush;
	std::string line;
	getline(std::cin, line);

	// Determine if the input should be a number or string.
	// String variables will end with a $ sign.

	bool isString = varName.find("$") == varName.length() - 1;

	Variable input;

	if (isString) {
		input = Variable(varName, Value(line));
	}
	else {
		// Is integer or decimal?
		bool isInt = line.find(".") == std::string::npos;
		if (isInt) {
			input = Variable(varName, Value(std::stoi(line)));
		}
		else {
			input = Variable(varName, Value(std::stod(line)));
		}
	}

	runtime.setVariable(input);

	return OK;
}
