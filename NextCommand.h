#pragma once
#include "Command.h"

class NextCommand : public Command
{
public:

	NextCommand(const std::vector<Lexeme>& lexemes,
		const std::string& varName);

	// Inherited via Command
	int invoke() override;

	static const std::string NEXT_COMMAND_NAME;

	std::string varName;
};

