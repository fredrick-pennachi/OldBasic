#pragma once

#include "Command.h"
#include "Lexeme.h"

#include <memory>
#include <stdexcept>
#include <vector>

class Parser
{
public:
	unique_ptr<Command> parse(const vector<Lexeme>& lexemes);

	unique_ptr<Command> parseId(const vector<Lexeme>& lexemes, int index);
};

class ParseException : public runtime_error {
public:
	ParseException(const string what);
};
