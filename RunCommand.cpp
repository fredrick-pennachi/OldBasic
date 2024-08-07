#include "RunCommand.h"

#include <iostream>

const std::string RunCommand::RUN_COMMAND_NAME = "RUN";

RunCommand::RunCommand(const std::vector<Lexeme>& lexemes) : Command(RUN_COMMAND_NAME, lexemes) {

}

int RunCommand::invoke(Runtime& runtime)
{
	runtime.run();

    return 0;
}
