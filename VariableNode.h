#pragma once
#include "ExpressionNode.h"
class VariableNode :
    public ExpressionNode
{
public:

    VariableNode(const Lexeme& lexeme);

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;
};
