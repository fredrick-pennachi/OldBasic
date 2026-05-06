/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include "Command.h"
#include "ExpressionNode.h"

#define GOSUB_COMMAND_NAME "GOSUB"
#define GOSUB_HELP "Jump to a line, then jump back on RETURN; GOSUB 500"

class GosubCommand :
    public Command
{
public:
	GosubCommand(const std::vector<Lexeme>& lexemes,
		std::unique_ptr<ExpressionNode> expression);

	// Inherited via Command
	CommandStatus invoke() override;

	std::unique_ptr<ExpressionNode> expression;
};
