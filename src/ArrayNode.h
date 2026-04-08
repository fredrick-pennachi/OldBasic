/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "ExpressionNode.h"

class ArrayNode :
    public ExpressionNode
{
public:
    ArrayNode(const Lexeme& lexeme, std::unique_ptr<ExpressionNode> subscript);

    // Inherited via ExpressionNode
    Value eval() override;

    bool evalBool() override;

    void print() override;

    std::string name;

    std::unique_ptr<ExpressionNode> subscript;
};
