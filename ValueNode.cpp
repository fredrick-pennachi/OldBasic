#include "ValueNode.h"

ValueNode::ValueNode(const Lexeme& lexeme) : ExpressionNode(lexeme, VALUE_NODE)
{
    if (lexeme.tokenName == INTEGER) {
        value = Value(stoi(lexeme.value));
    }
    else if (lexeme.tokenName == DBL_FLOAT) {
        value = Value(stof(lexeme.value));
    }
    else if (lexeme.tokenName == STRING) {
        value = Value(lexeme.value.substr(1, lexeme.value.size() - 2));
    }
    else {
        value = Value(lexeme.value);
    }
}

Value ValueNode::eval()
{
    return value;
}

bool ValueNode::evalBool()
{
    return value.evalBool();
}

void ValueNode::print()
{
    runtime << "ValueNode: " << lexeme.value << std::endl;
}
