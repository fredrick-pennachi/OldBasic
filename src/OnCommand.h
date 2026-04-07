
#pragma once
#include "Command.h"

class OnCommand :
    public Command

{
public:

    OnCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string ON_COMMAND_NAME;
};
