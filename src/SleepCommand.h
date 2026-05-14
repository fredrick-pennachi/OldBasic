/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"
#include "ExpressionNode.h"

#define SLEEP_COMMAND_NAME "SLEEP"
#define SLEEP_HELP "Sleeps for milliseconds; SLEEP 100"

class SleepCommand :
    public Command

{
public:

    SleepCommand(const std::vector<Lexeme>& lexemes,
        std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    std::unique_ptr<ExpressionNode> expression;
};
