#pragma once

#include "Command.h"

#include <string>

class GotoCommand : public Command {
public:
	GotoCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	int invoke() override;

	static const std::string GOTO_COMMAND_NAME;
};
