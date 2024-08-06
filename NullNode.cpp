#include "NullNode.h"

NullNode::NullNode() : ExpressionNode(lexeme, NULL_NODE)
{
}

Value NullNode::eval(Runtime& runtime)
{
    return Value();
}
