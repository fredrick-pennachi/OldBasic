
#pragma once
#include "Command.h"

class ReadCommand :
    public Command

{
public:

    ReadCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string READ_COMMAND_NAME;
};
