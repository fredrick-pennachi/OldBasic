// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "DrawCommand.h"

#include <iostream>

const std::string DrawCommand::DRAW_COMMAND_NAME = "DRAW";

DrawCommand::DrawCommand(const std::vector<Lexeme>& lexemes) : Command(DRAW_COMMAND_NAME, lexemes)
{
}

CommandStatus DrawCommand::invoke()
{
	runtime << "DrawCommand::invoke not implemented yet!" << std::endl;

	return OK;
}
