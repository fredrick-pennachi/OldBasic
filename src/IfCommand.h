#pragma once

#include "Command.h"
#include "ExpressionNode.h"

class IfCommand :
    public Command
{
public:
    IfCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression, std::unique_ptr<Command> command);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string IF_COMMAND_NAME;

    std::unique_ptr<ExpressionNode> expression;

    std::unique_ptr<Command> command;
};
