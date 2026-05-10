/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#include <string>

#define LOAD_COMMAND_NAME "LOAD"
#define LOAD_HELP "Loads a program from a file; LOAD \"program.bas\""

class LoadCommand : public Command {
public:
    LoadCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    std::unique_ptr<ExpressionNode> expression;
};
