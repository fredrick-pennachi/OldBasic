#pragma once
#include "Command.h"

class ReturnCommand :
    public Command
{
public:
	ReturnCommand(const std::vector<Lexeme>& lexemes);

	// Inherited via Command
	CommandStatus invoke() override;

    static const std::string RETURN_COMMAND_NAME;
};
