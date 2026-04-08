// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ClsCommand.h"

#include <iostream>

const std::string ClsCommand::CLS_COMMAND_NAME = "CLS";

ClsCommand::ClsCommand(const std::vector<Lexeme>& lexemes) : Command(CLS_COMMAND_NAME, lexemes)
{
}

CommandStatus ClsCommand::invoke()
{
	runtime.clearScreen();

	return OK;
}
