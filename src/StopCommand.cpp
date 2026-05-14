// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "StopCommand.h"

StopCommand::StopCommand(const std::vector<Lexeme>& lexemes)
	: Command(STOP_COMMAND_NAME, lexemes)
{
}

CommandStatus StopCommand::invoke()
{
	runtime.stop();

	return OK;
}
