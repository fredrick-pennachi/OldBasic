#include "NewCommand.h"

#include <iostream>

const std::string NewCommand::NEW_COMMAND_NAME = "NEW";

NewCommand::NewCommand(const std::vector<Lexeme>& lexemes) : Command(NEW_COMMAND_NAME, lexemes) {

}

int NewCommand::invoke()
{
	runtime.clear();

	return 0;
}
