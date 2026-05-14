/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#include <string>

#define PRINT_COMMAND_NAME "PRINT"
#define PRINT_HELP "Prints variable or value; PRINT A$; PRINT \"Hello!\""

class PrintCommand : public Command {
public:
    PrintCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    std::unique_ptr<ExpressionNode> expression;
};

