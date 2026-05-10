/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define NEXT_COMMAND_NAME "NEXT"
#define NEXT_HELP "Jumps to the start of FOR loop for next iteration; NEXT I"

class NextCommand : public Command
{
public:

	NextCommand(const std::vector<Lexeme>& lexemes,
		const std::string& varName);

	// Inherited via Command
	CommandStatus invoke() override;

	std::string varName;
};

