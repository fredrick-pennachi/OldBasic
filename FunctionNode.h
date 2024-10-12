#pragma once

#include "ExpressionNode.h"

#include <array>

class FunctionNode :
    public ExpressionNode
{
public:
    FunctionNode(const Lexeme& lexeme, std::unique_ptr<ExpressionNode> argument);

    const static std::array<const std::string, 2> functionNames;

    static bool isFunction(const std::string& id);

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;

    std::string name;

    std::unique_ptr<ExpressionNode> argument;
};
