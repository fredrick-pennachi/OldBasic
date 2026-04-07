#pragma once

#include "ExpressionNode.h"

class ValueNode :
    public ExpressionNode
{
public:

    ValueNode(const Lexeme& lexeme);

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;

    Value value;
};
