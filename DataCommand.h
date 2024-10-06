
#pragma once
#include "Command.h"

class DataCommand :
    public Command

{
public:

    DataCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string DATA_COMMAND_NAME;
};
