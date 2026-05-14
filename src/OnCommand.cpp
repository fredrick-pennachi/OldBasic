// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "OnCommand.h"

#include <iostream>

OnCommand::OnCommand(const std::vector<Lexeme>& lexemes) : Command(ON_COMMAND_NAME, lexemes)
{
}

CommandStatus OnCommand::invoke()
{
	runtime << "OnCommand::invoke not implemented yet!" << std::endl;

	return OK;
}
