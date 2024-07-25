#include "PrintCommand.h"

#include <iostream>
#include <sstream>

using namespace std;

const string PrintCommand::PRINT_COMMAND_NAME = "PRINT";

PrintCommand::PrintCommand(const vector<Lexeme>& lexemes) : Command(PRINT_COMMAND_NAME, lexemes)
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
	int i = 0;

	// Skip over the first lexeme if it's a line number.
	if (lexemes[i].tokenName == INTEGER) {
		i++;
	}

	// Skip over the PRINT id.
	i++;

	if (i == lexemes.size()) {
		// No argument, just print a newline.
		cout << endl;
	}
	else if (lexemes[i].tokenName == STRING) {
		// Print the string.
		cout << lexemes[i].value.substr(1, lexemes[i].value.size() - 2) << endl;

		return 0;
	}
	else if (lexemes[i].tokenName == ID) {
		// Print the string.
		Variable var = runtime.getVariable(lexemes[i].value);

		cout << var.value << endl;

		return 0;
	}

	stringstream ss;
	ss << (*this);

	throw InvalidSyntaxExeption("Unsupported syntax: "
		+ lexemes[i].value
		+ " in \"" + ss.str() + "\"");
}
