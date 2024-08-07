#include "OperatorNode.h"

OperatorNode::OperatorNode(
    const Lexeme& lexeme) :
        ExpressionNode(lexeme, OPERATOR_NODE)
{
}

Value OperatorNode::eval()
{
    if (lexeme.value == "*") {
        return left->eval() * right->eval();
    } else if (lexeme.value == "/") {
        return left->eval() / right->eval();
    } else if (lexeme.value == "+") {
        return left->eval() + right->eval();
    } else if (lexeme.value == "-") {
        return left->eval() - right->eval();
    }

    return Value();
}
