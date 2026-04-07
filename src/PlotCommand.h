
#pragma once
#include "Command.h"

class PlotCommand :
    public Command

{
public:

    PlotCommand(const std::vector<Lexeme>& lexemes);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string PLOT_COMMAND_NAME;
};
