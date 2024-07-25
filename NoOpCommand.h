#pragma once

#include "Command.h"

class NoOpCommand : public Command {
public:
	NoOpCommand(const vector<Lexeme>& lexemes);

	// Inherited via Command
	int invoke(Runtime& runtime) override;

	static const string NOOP_COMMAND_NAME;
};
