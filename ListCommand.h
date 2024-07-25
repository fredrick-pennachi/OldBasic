#pragma once
#include "Command.h"

class ListCommand : public Command {
public:
	ListCommand(const vector<Lexeme>& lexemes);

	// Inherited via Command
	int invoke(Runtime& runtime) override;

	static const string LIST_COMMAND_NAME;
};

