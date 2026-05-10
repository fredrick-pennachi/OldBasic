/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define NEW_COMMAND_NAME "NEW"
#define NEW_HELP "Erases the current program and resets the runtime; NEW"

class NewCommand :
    public Command
{
public:

    NewCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

};

