// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "ForCommand.h"
#include "MultiCommand.h"
#include "NextCommand.h"

const std::string MultiCommand::MULTI_COMMAND_NAME = "MULTI";


MultiCommand::MultiCommand(const std::vector<Lexeme>& lexemes)
	: Command(MULTI_COMMAND_NAME, lexemes)
{
}

CommandStatus MultiCommand::invoke()
{
	auto commandIter = commands.cbegin();

	while (commandIter != commands.cend())
	{
		// The loop logic is to support single line loops.

		int retVal = (*commandIter)->invoke();

		// If a Gosub jump occurred, execute that first.
		if (retVal == CALLER_SHOULD_BREAK) {
			break;
		}

		// Allow for nested loops by tracking nesting level.
		int nestCount = 0;

		if (retVal && (*commandIter)->name == NextCommand::NEXT_COMMAND_NAME) {

			do {
				commandIter--;

				if ((*commandIter)->name == NextCommand::NEXT_COMMAND_NAME) {
					nestCount++;
				}

				if ((*commandIter)->name == ForCommand::FOR_COMMAND_NAME) {
					if (nestCount == 0) {
						break;
					}
					else {
						nestCount--;
					}
				}
			} while (commandIter != commands.cbegin());
		}
		else {
			commandIter++;
		}
	}

	return OK;
}
