#include "MultiCommand.h"

const std::string MultiCommand::MULTI_COMMAND_NAME = "MULTI";


MultiCommand::MultiCommand(const std::vector<Lexeme>& lexemes)
	: Command(MULTI_COMMAND_NAME, lexemes)
{
}

int MultiCommand::invoke()
{
	for (std::unique_ptr<Command>& command : commands) {
		command->invoke();
	}

	return 0;
}
