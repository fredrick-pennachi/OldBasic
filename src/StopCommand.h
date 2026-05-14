/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define STOP_COMMAND_NAME "STOP"
#define STOP_HELP "Stops the running program."

class StopCommand :
	public Command
{
public:
	StopCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	CommandStatus invoke() override;
};
