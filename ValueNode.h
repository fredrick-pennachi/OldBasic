#pragma once

#include "ExpressionNode.h"

class ValueNode :
    public ExpressionNode
{
public:

    ValueNode(const Lexeme& lexeme);

    // Inherited via ExpressionNode
    Value eval(Runtime& runtime) override;

    Value value;
};
