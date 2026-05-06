/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#define DIM_COMMAND_NAME "DIM"
#define DIM_HELP "Declare an array; DIM A(10)"

class DimCommand :
    public Command
{
public:
    DimCommand(const std::vector<Lexeme>& lexemes, std::string arrayName, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    std::string arrayName;

    std::unique_ptr<ExpressionNode> expression;
};

