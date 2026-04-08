// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

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