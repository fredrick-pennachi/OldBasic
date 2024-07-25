#include "NoOpCommand.h"


const string NoOpCommand::NOOP_COMMAND_NAME = "NOOP";

NoOpCommand::NoOpCommand(const vector<Lexeme>& lexemes) : Command(NOOP_COMMAND_NAME, lexemes) {

}


int NoOpCommand::invoke(Runtime& runtime)
{
    return 0;
}
