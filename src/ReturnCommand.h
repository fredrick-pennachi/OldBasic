/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define RETURN_COMMAND_NAME "RETURN"
#define RETURN_HELP "Returns to the next line after a GOSUB invocation."

class ReturnCommand :
    public Command
{
public:
	ReturnCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	CommandStatus invoke() override;
};
