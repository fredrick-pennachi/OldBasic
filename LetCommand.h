#pragma once

#include "Command.h"
#include "ExpressionNode.h"

class LetCommand :
    public Command
{
public:
    LetCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    int invoke(Runtime& runtime) override;

    static const std::string LET_COMMAND_NAME;

    std::unique_ptr<ExpressionNode> expression;
};
