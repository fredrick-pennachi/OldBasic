/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"

class DimCommand :
    public Command
{
public:
    DimCommand(const std::vector<Lexeme>& lexemes, std::string arrayName, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string DIM_COMMAND_NAME;

    std::string arrayName;

    std::unique_ptr<ExpressionNode> expression;
};

