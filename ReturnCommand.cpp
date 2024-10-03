#include "ReturnCommand.h"

const std::string ReturnCommand::RETURN_COMMAND_NAME = "RETURN";

ReturnCommand::ReturnCommand(const std::vector<Lexeme>& lexemes)
	: Command(RETURN_COMMAND_NAME, lexemes)
{
}

CommandStatus ReturnCommand::invoke()
{
	runtime.returnGosub();

	return OK;
}
