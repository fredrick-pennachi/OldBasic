/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "ReadEval.h"

#include "Parser.h"
#include "RunCommand.h"
#include "Runtime.h"
#include "Tokenizer.h"

#include <fstream>

ReadEval readEval;

void ReadEval::readFile(std::string& filename)
{
	// Read the program file.
	std::ifstream programFile(filename); 
	std::string line;

	while (getline(programFile, line)) {
		// Eval the lines in the file.

		try {
			evalLine(line);
		}
		catch (std::exception& e) {
			runtime << u8"🐞 ERROR: " << e.what() << std::endl;
			runtime << u8"🐞 FROM : " << line << std::endl;
		}
	}

	// Close the file.
	programFile.close();
}

void ReadEval::evalLine(std::string& line)
{
	// Tokenize line
	std::vector<Lexeme> lexemes = tokenizer.tokenize(line);

	if (lexemes.size() == 0) {
		return;
	}

	// Turn tokens into command
	std::unique_ptr<Command> command = parser.parse(lexemes);
	// If first token is a line number then add to program
	// otherwise invoke immediately.
	if (lexemes[0].tokenName == INTEGER) {
		int lineNumber = stoi(lexemes[0].value);
		runtime.program[lineNumber] = move(command);
	}
	else {
		// No line number, invoke immediately.
		Command* commandPtr = command.get();

		if (commandPtr->name == RunCommand::RUN_COMMAND_NAME)
		{
			commandPtr->invoke();
		}
		else {
			// Write the line to line number zero to
			// support single line loops, then remove
			// it so that it isn't present for future
			// execution.
			runtime.program[0] = move(command);
			commandPtr->invoke();
			runtime.program.erase(0);
		}
	}
}
