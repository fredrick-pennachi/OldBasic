// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "HelpCommand.h"

#include "ClsCommand.h"
#include "DataCommand.h"
#include "DimCommand.h"
#include "DrawCommand.h"
#include "ForCommand.h"
#include "GosubCommand.h"
#include "GotoCommand.h"
#include "IfCommand.h"
#include "InputCommand.h"
#include "LetCommand.h"
#include "ListCommand.h"
#include "LoadCommand.h"
#include "MultiCommand.h"
#include "NewCommand.h"
#include "NextCommand.h"
#include "NoOpCommand.h"
#include "OnCommand.h"
#include "PlotCommand.h"
#include "PrintCommand.h"
#include "ReadCommand.h"
#include "ReturnCommand.h"
#include "RunCommand.h"
#include "SleepCommand.h"
#include "StopCommand.h"

#include <sstream>
#include <iomanip>

HelpCommand::HelpCommand(const std::vector<Lexeme>& lexemes)
	: Command(HELP_COMMAND_NAME, lexemes)
{
}

CommandStatus HelpCommand::invoke()
{
	std::stringstream ss;
	ss << "COMMANDS:\n";
	ss << std::setiosflags(std::ios::left);

#define HELP(name,help) ss << std::setw(7) << name << help << std::endl

	HELP(CLS_COMMAND_NAME, CLS_HELP);
	HELP(DIM_COMMAND_NAME, DIM_HELP);
	HELP(FOR_COMMAND_NAME, FOR_HELP);

#undef HELP(cn,ch)

	runtime << ss.str();

	return OK;
}
