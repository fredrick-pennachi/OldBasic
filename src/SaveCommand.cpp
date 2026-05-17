// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "SaveCommand.h"

#include "OperatorNode.h"
#include "ReadEval.h"

#include <string>
#include <iostream>
#include <fstream>

SaveCommand::SaveCommand(
	const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(SAVE_COMMAND_NAME, lexemes),
	expression(move(expression))
{
}

/*

SAVE ...

*/

CommandStatus SaveCommand::invoke()
{
	Value filename = expression->eval();

    std::ofstream ofs(filename.strValue);

    if (ofs.is_open()) {

        std::map<int, std::unique_ptr<Command>>::const_iterator it;
        it = runtime.program.cbegin();
        Command& command = *(*it).second;
        if (command.name == SAVE_COMMAND_NAME) {
            // Skip the in progress SAVE command.
            ++it;
        }

        for (; it != runtime.program.cend(); ++it) {
            command = *(*it).second;
            ofs << command << std::endl;
        }
        
        ofs.close();
        std::cout << u8"Program written successfully to " << filename << u8" 💾" << std::endl;

        return OK;
    }
    else {
        runtime << u8"🐞 ERROR: Unable to open file " << filename << u8" for writing!" << std::endl;
        return ERROR;
    }
}
