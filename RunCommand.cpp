#include "RunCommand.h"

#include <iostream>

const string RunCommand::RUN_COMMAND_NAME = "RUN";

RunCommand::RunCommand(vector<Lexeme>& lexemes) : Command(RUN_COMMAND_NAME, lexemes) {

}

int RunCommand::invoke(Runtime& runtime)
{
	runtime.run();

    return 0;
}
