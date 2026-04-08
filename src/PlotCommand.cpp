// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "PlotCommand.h"

#include <iostream>

const std::string PlotCommand::PLOT_COMMAND_NAME = "PLOT";

PlotCommand::PlotCommand(const std::vector<Lexeme>& lexemes) : Command(PLOT_COMMAND_NAME, lexemes)
{
}

CommandStatus PlotCommand::invoke()
{
	runtime << "PlotCommand::invoke not implemented yet!" << std::endl;

	return OK;
}
