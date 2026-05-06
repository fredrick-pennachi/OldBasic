/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"

#define HELP_COMMAND_NAME "HELP"
#define HELP_HELP "Prints the help for each command."

class HelpCommand :
    public Command
{   
public:
    HelpCommand(const std::vector<Lexeme>&lexemes);

    // Inherited via Command
    CommandStatus invoke() override;
};
