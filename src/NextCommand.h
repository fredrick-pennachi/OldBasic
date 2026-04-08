/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

class NextCommand : public Command
{
public:

	NextCommand(const std::vector<Lexeme>& lexemes,
		const std::string& varName);

	// Inherited via Command
	CommandStatus invoke() override;

	static const std::string NEXT_COMMAND_NAME;

	std::string varName;
};

