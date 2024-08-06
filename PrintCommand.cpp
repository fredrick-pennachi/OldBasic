#include "PrintCommand.h"

#include <iostream>
#include <sstream>

using namespace std;

const string PrintCommand::PRINT_COMMAND_NAME = "PRINT";

PrintCommand::PrintCommand(
	const vector<Lexeme>& lexemes,
	unique_ptr<ExpressionNode> expression)
	: Command(PRINT_COMMAND_NAME, lexemes),
	expression(move(expression))
{
}

/*

Forms of PRINT:

PRINT
PRINT "STRING"
PRINT STRING_VARIABLE$
PRINT 2 + 2

*/

int PrintCommand::invoke(Runtime& runtime)
{
	if (expression) {
		Value value = expression->eval(runtime);
		cout << value << endl;
	}
	else {
		// No argument, just print a newline.
		cout << endl;
	}

	return 0;
}
