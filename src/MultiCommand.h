/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"

#include <vector>

#define MULTI_COMMAND_NAME "MULTI"
#define MULTI_HELP "Colon allows multiple commands on same line; LET C = C + 1 : PRINT C"

class MultiCommand :
    public Command
{   
public:
    MultiCommand(const std::vector<Lexeme>&lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    std::vector<std::unique_ptr<Command>> commands;
};
