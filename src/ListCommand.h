/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

class ListCommand : public Command {
public:
	ListCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	CommandStatus invoke() override;

	static const std::string LIST_COMMAND_NAME;
};

