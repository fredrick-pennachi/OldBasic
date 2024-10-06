
#pragma once
#include "Command.h"

class ClsCommand :
    public Command

{
public:

    ClsCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string CLS_COMMAND_NAME;
};
