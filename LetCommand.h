#pragma once

#include "Command.h"
#include "ExpressionNode.h"

class LetCommand :
    public Command
{
public:
    LetCommand(const vector<Lexeme>& lexemes, unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    int invoke(Runtime& runtime) override;

    static const string LET_COMMAND_NAME;

    unique_ptr<ExpressionNode> expression;
};
