// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "LoadCommand.h"

#include "OperatorNode.h"
#include "ReadEval.h"

#include <string>

LoadCommand::LoadCommand(
	const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(LOAD_COMMAND_NAME, lexemes),
	expression(move(expression))
{
}

/*

LOAD ...

*/

CommandStatus LoadCommand::invoke()
{
	Value filename = expression->eval();

	// Read the program file.
	
	readEval.readFile(filename.strValue);

	return OK;
}
