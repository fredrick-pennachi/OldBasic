/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"
#include "OperatorNode.h"

#define FOR_COMMAND_NAME "FOR"
#define FOR_HELP "Start loop over range (end loop with NEXT); FOR I = 1 TO 10"

class ForCommand :
    public Command
{
public:

    ForCommand(const std::vector<Lexeme>& lexemes,
        std::unique_ptr<ExpressionNode> initExpr,
        std::unique_ptr<ExpressionNode> toExpr);

    // Inherited via Command
    CommandStatus invoke() override;

    int reset();

    std::unique_ptr<OperatorNode> initExpr;
    std::unique_ptr<ExpressionNode> toExpr;

    std::string varName;
};

