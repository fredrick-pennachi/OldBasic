#include "VariableNode.h"

VariableNode::VariableNode(const Lexeme& lexeme) : ExpressionNode(lexeme, VARIABLE_NODE)
{
}

Value VariableNode::eval()
{
    return Value();
}
