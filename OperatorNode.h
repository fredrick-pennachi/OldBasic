#pragma once

#include "ExpressionNode.h"

class OperatorNode : public ExpressionNode
{
public:
	OperatorNode(const Lexeme& lexeme);

	// Inherited via ExpressionNode
	Value eval(Runtime& runtime) override;

	unique_ptr<ExpressionNode> left;
	unique_ptr<ExpressionNode> right;
};
