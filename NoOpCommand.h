#pragma once

#include "Command.h"

class NoOpCommand : public Command {
public:
	NoOpCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	int invoke(Runtime& runtime) override;

	static const std::string NOOP_COMMAND_NAME;
};
