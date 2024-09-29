#include "StopCommand.h"

const std::string StopCommand::STOP_COMMAND_NAME = "STOP";

StopCommand::StopCommand(const std::vector<Lexeme>& lexemes)
	: Command(STOP_COMMAND_NAME, lexemes)
{
}

int StopCommand::invoke()
{
	runtime.stop();

	return 0;
}
