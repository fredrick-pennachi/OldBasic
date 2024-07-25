#pragma once

#include "Command.h"

#include <string>

class GotoCommand : public Command {
public:
	GotoCommand(const vector<Lexeme>& lexemes);

	// Inherited via Command
	int invoke(Runtime& runtime) override;

	static const string GOTO_COMMAND_NAME;
};
