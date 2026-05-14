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
	HELP(GOSUB_COMMAND_NAME, GOSUB_HELP);
	HELP(GOTO_COMMAND_NAME, GOTO_HELP);
	HELP(HELP_COMMAND_NAME, HELP_HELP);
	HELP(IF_COMMAND_NAME, IF_HELP);
	HELP(INPUT_COMMAND_NAME, INPUT_HELP);
	HELP(LET_COMMAND_NAME, LET_HELP);
	HELP(LIST_COMMAND_NAME, LIST_HELP);
	HELP(LOAD_COMMAND_NAME, LOAD_HELP);
	HELP(MULTI_COMMAND_NAME, MULTI_HELP);
	HELP(NEW_COMMAND_NAME, NEW_HELP);
	HELP(NEXT_COMMAND_NAME, NEXT_HELP);
	HELP(PRINT_COMMAND_NAME, PRINT_HELP);
	HELP(READ_COMMAND_NAME, READ_HELP);
	HELP(RETURN_COMMAND_NAME, RETURN_HELP);
	HELP(RUN_COMMAND_NAME, RUN_HELP);
	HELP(SLEEP_COMMAND_NAME, SLEEP_HELP);
	HELP(STOP_COMMAND_NAME, STOP_HELP);
	
#undef HELP(cn,ch)

	runtime << ss.str();

	return OK;
}
