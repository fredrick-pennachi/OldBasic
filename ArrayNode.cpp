#include "ArrayNode.h"

ArrayNode::ArrayNode(const Lexeme& lexeme, std::unique_ptr<ExpressionNode> subscript)
    : ExpressionNode(lexeme, ARRAY_NODE), subscript(std::move(subscript))
{
}

Value ArrayNode::eval()
{
    if (lexeme.tokenName == ID) {
        // Retrieve the value for this array index.
        return runtime.getArrayValue(lexeme.value, subscript->eval().intValue);
    }
    else {
        // An array expression really needs to have an id!
        throw ExpressionException("An array expression must be named!");
    }
}

bool ArrayNode::evalBool()
{
    return eval().evalBool();
}

void ArrayNode::print()
{
    runtime << "ArrayNode: " << lexeme.value
        << "(" << subscript->eval() << ")" << std::endl;
}
