#include "NullNode.h"

NullNode::NullNode() : ExpressionNode(lexeme, NULL_NODE)
{
}

Value NullNode::eval()
{
    return Value();
}

bool NullNode::evalBool()
{
    return false;
}

void NullNode::print()
{
    runtime << "NullNode" << std::endl;
}