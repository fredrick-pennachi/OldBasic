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
	int i = 0;

	// Skip over the first lexeme if it's a line number.
	if (lexemes[i].tokenName == INTEGER) {
		i++;
	}

	// Skip over the LET id.
	i++;

	if (i == lexemes.size()) {
		// No argument, this isn't valid for LET.
		std::stringstream ss;
		ss << (*this);

		throw InvalidSyntaxExeption("Unsupported syntax: No argument isn't valid for LET.");
	}
	else if (lexemes[i].tokenName == ID) {
		std::string name = lexemes[i].value;

		i++;
		if (lexemes[i].value == "=") {
			i++;

			// Declare the variable and value in the runtime.
			if (lexemes[i].tokenName == INTEGER || lexemes[i].tokenName == STRING) {
				runtime.setVariable(name, lexemes[i].value);
				return 0;
			}
		}		
	}

	std::stringstream ss;
	ss << (*this);

	throw InvalidSyntaxExeption("Unsupported syntax: "
		+ lexemes[i].value
		+ " in \"" + ss.str() + "\"");
}
