#include "FunctionNode.h"

#include <random>

FunctionNode::FunctionNode(const Lexeme& lexeme, std::unique_ptr<ExpressionNode> subscript)
    : ExpressionNode(lexeme, FUNCTION_NODE), subscript(std::move(subscript))
{
    if (lexeme.tokenName == ID) {
        // Retrieve the name of this function.
        this->name = lexeme.value;
    }
    else {
        // An array expression really needs to have an id!
        throw ExpressionException("A function expression must be named!");
    }
}

Value FunctionNode::eval()
{
    std::default_random_engine generator(time(nullptr));
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return Value(distribution(generator));
}

bool FunctionNode::evalBool()
{
    return eval().evalBool();
}

void FunctionNode::print()
{
    runtime << "FunctionNode: " << name
        << "(" << subscript->eval() << ")" << std::endl;
}
