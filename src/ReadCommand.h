/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define READ_COMMAND_NAME "READ"
#define READ_HELP "Copies next value of DATA into variable; READ A$"

class ReadCommand :
    public Command

{
public:

    ReadCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;
};
