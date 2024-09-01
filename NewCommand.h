#pragma once
#include "Command.h"

class NewCommand :
    public Command
{
public:

    NewCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    int invoke() override;

    static const std::string NEW_COMMAND_NAME;
};

