/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#define IF_COMMAND_NAME "IF"
#define IF_HELP "Conditional expression; IF 2 > 1 THEN PRINT \"GREATER!\""

class IfCommand :
    public Command
{
public:
    IfCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression, std::unique_ptr<Command> command);

    // Inherited via Command
    CommandStatus invoke() override;

    std::unique_ptr<ExpressionNode> expression;

    std::unique_ptr<Command> command;
};
