#pragma once

#include "Command.h"

#include <vector>

class MultiCommand :
    public Command
{   
public:
    MultiCommand(const std::vector<Lexeme>&lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string MULTI_COMMAND_NAME;

    std::vector<std::unique_ptr<Command>> commands;
};
