#pragma once

#include "Command.h"
#include "ExpressionNode.h"
#include "OperatorNode.h"

class LetCommand :
    public Command
{
public:
    LetCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    int invoke() override;

    static const std::string LET_COMMAND_NAME;

    std::unique_ptr<OperatorNode> assignExpr;
};
