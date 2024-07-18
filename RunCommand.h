#pragma once
#include "Command.h"

class RunCommand :
    public Command
{
public:

    RunCommand(vector<Lexeme>& lexemes);

    // Inherited via Command
    int invoke(Runtime& runtime) override;

    static const string RUN_COMMAND_NAME;
};

