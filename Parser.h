#pragma once

#include "Command.h"
#include "ExpressionNode.h"
#include "Lexeme.h"

#include <memory>
#include <stack>
#include <stdexcept>
#include <vector>



class Parser
{
public:
	std::unique_ptr<Command> parse(const std::vector<Lexeme>& lexemes);

	std::unique_ptr<Command> parseId(const std::vector<Lexeme>& lexemes, int index);

	std::unique_ptr<ExpressionNode> parseExpression(const std::vector<Lexeme>& lexemes);
};

std::ostream& operator<<(std::ostream& os, std::stack<Lexeme> stack);

class ParseException : public std::runtime_error {
public:
	ParseException(const std::string what);
};
