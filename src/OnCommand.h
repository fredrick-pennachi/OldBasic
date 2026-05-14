/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define ON_COMMAND_NAME "ON"
#define ON_HELP "Jump to line based on an index variable; ON a GOTO 100,200,300"

class OnCommand :
    public Command
{
public:

    OnCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;
};
