#include "NoOpCommand.h"


const std::string NoOpCommand::NOOP_COMMAND_NAME = "NOOP";

NoOpCommand::NoOpCommand(const std::vector<Lexeme>& lexemes) : Command(NOOP_COMMAND_NAME, lexemes) {

}


int NoOpCommand::invoke()
{
    return 0;
}
