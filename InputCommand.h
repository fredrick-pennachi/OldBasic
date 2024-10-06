
#pragma once
#include "Command.h"

class InputCommand :
    public Command

{
public:

    InputCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string INPUT_COMMAND_NAME;
};
