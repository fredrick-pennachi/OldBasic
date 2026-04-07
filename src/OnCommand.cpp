
#include "OnCommand.h"

#include <iostream>

const std::string OnCommand::ON_COMMAND_NAME = "ON";

OnCommand::OnCommand(const std::vector<Lexeme>& lexemes) : Command(ON_COMMAND_NAME, lexemes)
{
}

CommandStatus OnCommand::invoke()
{
	runtime << "OnCommand::invoke not implemented yet!" << std::endl;

	return OK;
}
