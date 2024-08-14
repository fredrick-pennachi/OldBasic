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
}

//int GotoCommand::invoke() {
//	
//	int i = 0;
//
//	// Skip over the first lexeme if it's a line number.
//	if (lexemes[i].tokenName == INTEGER) {
//		i++;
//	}
//
//	// Skip over the GOTO id.
//	i++;
//
//	if (i == lexemes.size()) {
//		// No argument, this isn't supported for GOTO.
//		std::stringstream ss;
//		ss << (*this);
//
//		throw InvalidSyntaxException("Unsupported syntax: Missing line number in \"" + ss.str() + "\"");
//	}
//	else if (lexemes[i].tokenName == INTEGER) {
//		// Set the next line of the program.
//		int lineNumber = stoi(lexemes[i].value);
//		runtime.setNextLine(lineNumber);
//	}
//	else {
//		std::stringstream ss;
//		ss << (*this);
//
//		throw InvalidSyntaxException("Unsupported syntax: "
//			+ lexemes[i].value
//			+ " in \"" + ss.str() + "\"");
//	}
//
//	return 0;
//}
