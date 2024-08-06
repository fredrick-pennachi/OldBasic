#include "OperatorNode.h"

OperatorNode::OperatorNode(
    const Lexeme& lexeme) :
        ExpressionNode(lexeme, OPERATOR_NODE)
{
}

Value OperatorNode::eval(Runtime& runtime)
{
    if (lexeme.value == "*") {
        return left->eval(runtime) * right->eval(runtime);
    } else if (lexeme.value == "/") {
        return left->eval(runtime) / right->eval(runtime);
    } else if (lexeme.value == "+") {
        return left->eval(runtime) + right->eval(runtime);
    } else if (lexeme.value == "-") {
        return left->eval(runtime) - right->eval(runtime);
    }

    return Value();
}
