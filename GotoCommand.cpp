#include "GotoCommand.h"

#include <iostream>
#include <sstream>

const std::string GotoCommand::GOTO_COMMAND_NAME = "GOTO";

GotoCommand::GotoCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression)
	: Command(GOTO_COMMAND_NAME, lexemes), expression(move(expression)) {
}

/*

Forms of GOTO:

GOTO 10
GOTO 10 * 5
GOTO A (where A == 10)

*/

int GotoCommand::invoke()
{
	Value val = expression->eval();

	if (val.getType() != ValueType::INTEGER) {
		throw InvalidSyntaxException("Unsupported syntax: line number in GOTO must be integer!");
	}
	else {
		// Set the next line of the program.
		runtime.setNextLine(val.intValue);
	}

	return 0;
}
