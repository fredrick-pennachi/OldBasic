/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "ExpressionNode.h"

class NullNode :
    public ExpressionNode
{
public:
    NullNode();

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;
};
