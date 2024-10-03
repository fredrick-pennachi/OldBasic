#pragma once

#include "Command.h"

class NoOpCommand : public Command {
public:
	NoOpCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	CommandStatus invoke() override;

	static const std::string NOOP_COMMAND_NAME;
};
