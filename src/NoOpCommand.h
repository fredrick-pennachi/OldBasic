/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"

#define NOOP_COMMAND_NAME "NOOP"
#define NOOP_HELP "Used as a placeholder internally."

class NoOpCommand : public Command {
public:
	NoOpCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	CommandStatus invoke() override;

};
