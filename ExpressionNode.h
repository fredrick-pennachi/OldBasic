#pragma once

#include "Runtime.h"
#include "Value.h"

class ExpressionNode
{
public:
	enum NodeType { NULL_NODE, OPERATOR_NODE, VALUE_NODE, VARIABLE_NODE };

	ExpressionNode(const Lexeme& lexeme, NodeType nodeType);

	virtual Value eval() = 0;

	Lexeme lexeme;

	NodeType nodeType;
};

class ExpressionException : public std::runtime_error {
public:
	ExpressionException(std::string what);
};
