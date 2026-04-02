#pragma once

#include "ExpressionNode.h"

#include <array>
#include <random>

class FunctionNode :
    public ExpressionNode
{
public:
    FunctionNode(const Lexeme& lexeme, std::unique_ptr<ExpressionNode> argument);

    const static std::array<const std::string, 10> functionNames;

    static bool isFunction(const std::string& id);

    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution;

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;

    std::string name;

    std::unique_ptr<ExpressionNode> argument;
};
