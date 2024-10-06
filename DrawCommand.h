
#pragma once
#include "Command.h"

class DrawCommand :
    public Command

{
public:

    DrawCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string DRAW_COMMAND_NAME;
};
