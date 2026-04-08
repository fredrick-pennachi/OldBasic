// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "StopCommand.h"

const std::string StopCommand::STOP_COMMAND_NAME = "STOP";

StopCommand::StopCommand(const std::vector<Lexeme>& lexemes)
	: Command(STOP_COMMAND_NAME, lexemes)
{
}

CommandStatus StopCommand::invoke()
{
	runtime.stop();

	return OK;
}
