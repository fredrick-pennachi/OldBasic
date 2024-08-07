#include "NullNode.h"

NullNode::NullNode() : ExpressionNode(lexeme, NULL_NODE)
{
}

Value NullNode::eval()
{
    return Value();
}
