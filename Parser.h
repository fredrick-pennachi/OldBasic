#pragma once

#include "Command.h"
#include "Lexeme.h"

#include <memory>
#include <stdexcept>
#include <vector>

class Parser
{
public:
	unique_ptr<Command> parse(vector<Lexeme>& lexemes);

	unique_ptr<Command> parseId(vector<Lexeme>& lexemes, int index);
};

class ParseException : public runtime_error {
public:
	ParseException(string what);
};
