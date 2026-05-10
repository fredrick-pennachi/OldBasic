/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#define LET_COMMAND_NAME "LET"
#define LET_HELP "Instantiate a variable and assign a value; LET C = 3"

class LetCommand :
    public Command
{
public:
    
    LetCommand(const std::vector<Lexeme>& lexemes);
    
    LetCommand(const std::vector<Lexeme>& lexemes,
        std::unique_ptr<ExpressionNode> variable,
        std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    std::unique_ptr<ExpressionNode> variable;
    std::unique_ptr<ExpressionNode> expression;
};
