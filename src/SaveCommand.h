/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#include <string>

#define SAVE_COMMAND_NAME "SAVE"
#define SAVE_HELP "Saves the program to a file; SAVE \"program.bas\""

class SaveCommand : public Command {
public:
    SaveCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    std::unique_ptr<ExpressionNode> expression;
};
