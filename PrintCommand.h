#pragma once

#include "Command.h"

#include <string>

class PrintCommand : public Command {
public:

    PrintCommand(vector<Lexeme>& lexemes);

    // Inherited via Command
    int invoke(Runtime& runtime) override;

    static const string PRINT_COMMAND_NAME;
};

