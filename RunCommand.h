#pragma once
#include "Command.h"

class RunCommand :
    public Command
{
public:

    RunCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string RUN_COMMAND_NAME;
};

