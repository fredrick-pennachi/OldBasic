#pragma once
#include "ExpressionNode.h"

class NullNode :
    public ExpressionNode
{
public:
    NullNode();

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;
};
