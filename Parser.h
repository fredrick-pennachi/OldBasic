#pragma once

#include "Command.h"
#include "ExpressionNode.h"
#include "Lexeme.h"

#include <memory>
#include <stack>
#include <stdexcept>
#include <vector>

using namespace std;

class Parser
{
public:
	unique_ptr<Command> parse(const vector<Lexeme>& lexemes);

	unique_ptr<Command> parseId(const vector<Lexeme>& lexemes, int index);

	unique_ptr<ExpressionNode> parseExpression(const vector<Lexeme>& lexemes);
};

ostream& operator<<(ostream& os, stack<Lexeme> stack);

class ParseException : public runtime_error {
public:
	ParseException(const string what);
};
