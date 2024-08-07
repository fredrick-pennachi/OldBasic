#include "ListCommand.h"

#include <iostream>

const std::string ListCommand::LIST_COMMAND_NAME = "LIST";

ListCommand::ListCommand(const std::vector<Lexeme>& lexemes) : Command(LIST_COMMAND_NAME, lexemes) {
}

int ListCommand::invoke()
{
	std::map<int, std::unique_ptr<Command>>::const_iterator it;

	for (it = runtime.program.cbegin(); it != runtime.program.cend(); it++) {
		Command& command = *(*it).second;
		runtime << command << std::endl;
	}

	return 0;
}
