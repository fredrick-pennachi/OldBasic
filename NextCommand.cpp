#include "ForCommand.h"
#include "MultiCommand.h"
#include "NextCommand.h"

const std::string NextCommand::NEXT_COMMAND_NAME = "NEXT";

NextCommand::NextCommand(const std::vector<Lexeme>& lexemes,
	const std::string& varName)
	: Command(NEXT_COMMAND_NAME, lexemes) ,varName(varName)
{
}

int NextCommand::invoke()
{
	// Get the line number for the FOR loop by varName.
	auto lineNumIter = runtime.forLoops.find(varName);

	if (lineNumIter == runtime.forLoops.end()) {
		throw RuntimeException("NEXT FOR loop not found in Runtime!");
	}

	int lineNum = lineNumIter->second;

	// Get the FOR Command.
	auto programIter = runtime.program.find(lineNum);

	if (programIter == runtime.program.end()) {
		throw RuntimeException("NEXT line number not found in program!");
	}

	Command* command = runtime.program[lineNum].get();

	ForCommand* forCommand = dynamic_cast<ForCommand*>(command);

	if (!forCommand) {

		// Check if it's a MultiCommand.
		MultiCommand* multiCommand = dynamic_cast<MultiCommand*>(command);

		if (multiCommand) {

			for (auto commandIter = multiCommand->commands.cbegin();
				commandIter != multiCommand->commands.cend(); commandIter++) {

				forCommand = dynamic_cast<ForCommand*>((*commandIter).get());

				if (forCommand) {
					if (forCommand->varName == varName) {
						// FOR is part of a MultiCommand, that's okay.
						break;
					}
					else {
						forCommand = NULL;
					}
				}
			}
		}

		if (!forCommand) {
			throw RuntimeException("NEXT lineNum doesn't contain FOR!");
		}
	}

	// Evaluate the loop condition.

	Value toVal = forCommand->toExpr->eval();
	Value currentVal = runtime.getVariable(varName).value;

	if (currentVal < toVal) {
		runtime.setNextLine(lineNum);

		// Return 1 to indicate that the program should loop.
		// Is currently used in single line, immediate evaluation
		// without line numbers.
		return 1;
	}
	else {
		// Loop is finished, reset the FOR loop so
		// it will be re-initialized if called again.
		forCommand->reset();

		// Return 0 to indicate that looping is finished.
		return 0;
	}
}
