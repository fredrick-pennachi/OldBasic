#include "PrintCommand.h"

#include <iostream>
#include <sstream>



const std::string PrintCommand::PRINT_COMMAND_NAME = "PRINT";

PrintCommand::PrintCommand(
	const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(PRINT_COMMAND_NAME, lexemes),
	expression(move(expression))
{
}

/*

Forms of PRINT:

PRINT
PRINT "std::string"
PRINT std::string_VARIABLE$
PRINT 2 + 2

*/

int PrintCommand::invoke(Runtime& runtime)
{
	if (expression) {
		Value value = expression->eval(runtime);
		std::cout << value << std::endl;
	}
	else {
		// No argument, just print a newline.
		std::cout << std::endl;
	}

	return 0;
}
