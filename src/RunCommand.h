/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define RUN_COMMAND_NAME "RUN"
#define RUN_HELP "Runs the program."

class RunCommand :
    public Command
{
public:

    RunCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;
};

