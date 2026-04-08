// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ArrayNode.h"

ArrayNode::ArrayNode(const Lexeme& lexeme, std::unique_ptr<ExpressionNode> subscript)
    : ExpressionNode(lexeme, ARRAY_NODE), subscript(std::move(subscript))
{
    if (lexeme.tokenName == ID) {
        // Retrieve the value for this array index.
        this->name = lexeme.value;
    }
    else {
        // An array expression really needs to have an id!
        throw ExpressionException("An array expression must be named!");
    }
}

Value ArrayNode::eval()
{
    if (runtime.hasArray(name)) {
        return runtime.getArrayValue(name, subscript->eval().intValue);
    }
    else {
        throw ExpressionException("No array with the name \"" + name + "\" exists!");
    }
    
}

bool ArrayNode::evalBool()
{
    return eval().evalBool();
}

void ArrayNode::print()
{
    runtime << "ArrayNode: " << name
        << "(" << subscript->eval() << ")" << std::endl;
}
