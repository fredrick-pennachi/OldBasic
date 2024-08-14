#pragma once

#include "ExpressionNode.h"

class OperatorNode : public ExpressionNode
{
public:
	OperatorNode(const Lexeme& lexeme);

	// Inherited via ExpressionNode
	Value eval() override;

	bool evalBool() override;

	void print() override;

	std::unique_ptr<ExpressionNode> left;
	std::unique_ptr<ExpressionNode> right;
};
