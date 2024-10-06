
#include "ClsCommand.h"

#include <iostream>

const std::string ClsCommand::CLS_COMMAND_NAME = "CLS";

ClsCommand::ClsCommand(const std::vector<Lexeme>& lexemes) : Command(CLS_COMMAND_NAME, lexemes)
{
}

CommandStatus ClsCommand::invoke()
{
	runtime << "ClsCommand::invoke not implemented yet!" << std::endl;

	return OK;
}
