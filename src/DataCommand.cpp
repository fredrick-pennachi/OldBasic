
#include "DataCommand.h"

#include <iostream>

const std::string DataCommand::DATA_COMMAND_NAME = "DATA";

DataCommand::DataCommand(const std::vector<Lexeme>& lexemes) : Command(DATA_COMMAND_NAME, lexemes)
{
}

CommandStatus DataCommand::invoke()
{
	runtime << "DataCommand::invoke not implemented yet!" << std::endl;

	return OK;
}
