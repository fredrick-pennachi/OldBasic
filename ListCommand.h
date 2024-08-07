#pragma once
#include "Command.h"

class ListCommand : public Command {
public:
	ListCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	int invoke(Runtime& runtime) override;

	static const std::string LIST_COMMAND_NAME;
};

