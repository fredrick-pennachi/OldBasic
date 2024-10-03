#pragma once
#include "Command.h"

class StopCommand :
	public Command
{
public:
	StopCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	CommandStatus invoke() override;

	static const std::string STOP_COMMAND_NAME;
};
