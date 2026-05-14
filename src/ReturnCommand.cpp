// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ReturnCommand.h"

ReturnCommand::ReturnCommand(const std::vector<Lexeme>& lexemes)
	: Command(RETURN_COMMAND_NAME, lexemes)
{
}

CommandStatus ReturnCommand::invoke()
{
	runtime.returnGosub();

	return OK;
}
