#pragma once
#include "Command.h"
class LetCommand :
    public Command
{
public:
    LetCommand(vector<Lexeme>& lexemes);

    // Inherited via Command
    int invoke(Runtime& runtime) override;

    static const string LET_COMMAND_NAME;
};
