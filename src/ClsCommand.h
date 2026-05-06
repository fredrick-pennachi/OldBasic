/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define CLS_COMMAND_NAME "CLS"
#define CLS_HELP "Clears the screen."

class ClsCommand :
    public Command

{
public:

    ClsCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;
};
