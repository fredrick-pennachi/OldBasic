
#include "ReadCommand.h"

#include <iostream>

const std::string ReadCommand::READ_COMMAND_NAME = "READ";

ReadCommand::ReadCommand(const std::vector<Lexeme>& lexemes) : Command(READ_COMMAND_NAME, lexemes)
{
}

CommandStatus ReadCommand::invoke()
{
	runtime << "ReadCommand::invoke not implemented yet!" << std::endl;

	return OK;
}
