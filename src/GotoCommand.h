/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#include <string>

#define GOTO_COMMAND_NAME "GOTO"
#define GOTO_HELP "Jump to a line and continue execution; GOTO 10"

class GotoCommand : public Command {
public:
	GotoCommand(const std::vector<Lexeme>& lexemes,
		std::unique_ptr<ExpressionNode> expression);

	// Inherited via Command
	CommandStatus invoke() override;

	std::unique_ptr<ExpressionNode> expression;
};
