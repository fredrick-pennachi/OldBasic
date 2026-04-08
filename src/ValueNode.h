/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "ExpressionNode.h"

class ValueNode :
    public ExpressionNode
{
public:

    ValueNode(const Lexeme& lexeme);

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;

    Value value;
};
