
#include "InputCommand.h"

#include <iostream>

const std::string InputCommand::INPUT_COMMAND_NAME = "INPUT";

InputCommand::InputCommand(const std::vector<Lexeme>& lexemes) : Command(INPUT_COMMAND_NAME, lexemes)
{
}

CommandStatus InputCommand::invoke()
{
	runtime << "InputCommand::invoke not implemented yet!" << std::endl;

	return OK;
}
