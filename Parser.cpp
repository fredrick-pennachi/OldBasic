#include "Parser.h"

#include "GotoCommand.h"
#include "LetCommand.h"
#include "ListCommand.h"
#include "NoOpCommand.h"
#include "PrintCommand.h"
#include "RunCommand.h"

unique_ptr<Command> Parser::parse(vector<Lexeme>& lexemes) {

	if (lexemes.empty()) {
		// Not sure how the program would get here.
		return make_unique<NoOpCommand>(lexemes);
	}

	int currentIndex = 0;

	if (lexemes[currentIndex].tokenName == INTEGER) {
		if (lexemes.size() == 1) {
			return make_unique<NoOpCommand>(lexemes);
		}
		else {
			// Skip past the line number.
			currentIndex++;
		}
	}

	TokenName tokenName = lexemes[currentIndex].tokenName;
	// Only ID should be valid in this position.
	switch (tokenName) {
	case ID:
		return parseId(lexemes, currentIndex);
	case UNSET:
	case INTEGER:
	case OPERATOR:
	case SEPARATOR:
	case STRING:
	default:
		throw ParseException("Parsing error, unexpected token " + TokenNameMap.at(tokenName) + ".");
	}
}

unique_ptr<Command> Parser::parseId(vector<Lexeme>& lexemes, int index)
{
	string& id = lexemes[index].value;

	// Is this a command?

	// Maybe this logic should be tidied up with sets of commands and functions.
	if (id == "PRINT") {
		return make_unique<PrintCommand>(lexemes);
	}
	else if (id == "GOTO") {
		return make_unique<GotoCommand>(lexemes);
	}
	else if (id == "LET") {
		return make_unique<LetCommand>(lexemes);
	}
	else if (id == "LIST") {
		return make_unique<ListCommand>(lexemes);
	}
	else if (id == "RUN") {
		return make_unique<RunCommand>(lexemes);
	}

	// Is it an existing variable?

	throw ParseException("Parsing error, unknown id " + id + ".");
}

ParseException::ParseException(string what) : runtime_error(what)
{
}
