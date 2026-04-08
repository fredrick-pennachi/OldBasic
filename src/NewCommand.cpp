// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "NewCommand.h"

#include <iostream>

const std::string NewCommand::NEW_COMMAND_NAME = "NEW";

NewCommand::NewCommand(const std::vector<Lexeme>& lexemes) : Command(NEW_COMMAND_NAME, lexemes) {

}

CommandStatus NewCommand::invoke()
{
	runtime.clearProgram();

	return OK;
}
