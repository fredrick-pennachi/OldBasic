#pragma once

#include "ExpressionNode.h"

class FunctionNode :
    public ExpressionNode
{
public:
    FunctionNode(const Lexeme& lexeme, std::unique_ptr<ExpressionNode> subscript);

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;

    std::string name;

    std::unique_ptr<ExpressionNode> subscript;
};
