#include "LetCommand.h"

#include <sstream>

using namespace std;

const string LetCommand::LET_COMMAND_NAME = "LET";

LetCommand::LetCommand(vector<Lexeme>& lexemes) : Command(LET_COMMAND_NAME, lexemes)
{
}

/*

Forms of LET:

LET A = 1
LET B$ = "B"

*/

int LetCommand::invoke(Runtime& runtime)
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
		stringstream ss;
		ss << (*this);

		throw InvalidSyntaxExeption("Unsupported syntax: No argument isn't valid for LET.");
	}
	else if (lexemes[i].tokenName == ID) {
		// String variable names should end in $.
		bool isString = false;
		if (lexemes[i].value[lexemes[i].value.size() - 1] == '$') {
			isString = true;
		}
		i++;
		if (lexemes[i].value == "=") {
			i++;


			if (lexemes[i].tokenName == INTEGER) {
				int varValue = stoi(lexemes[i].value);

			}
			else if (lexemes[i].tokenName == STRING) {
				string varValue = lexemes[i].value;

			}
		}
	}

	stringstream ss;
	ss << (*this);

	throw InvalidSyntaxExeption("Unsupported syntax: "
		+ lexemes[i].value
		+ " in \"" + ss.str() + "\"");
}

