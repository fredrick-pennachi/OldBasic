#pragma once

#include "ExpressionNode.h"

#include <map>

class OperatorNode : public ExpressionNode
{
public:
	OperatorNode(const Lexeme& lexeme);

	// Inherited via ExpressionNode
	Value eval() override;

	bool evalBool() override;

	void print() override;

	int getPrecendence();

	std::unique_ptr<ExpressionNode> left;
	std::unique_ptr<ExpressionNode> right;

	static std::map<std::string, int> Precedence;
};
