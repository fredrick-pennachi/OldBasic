/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"

#define LIST_COMMAND_NAME "LIST"
#define LIST_HELP "Displays the program line by line."

class ListCommand : public Command {
public:
	ListCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	CommandStatus invoke() override;
};

