#pragma once

#include "Command.h"
#include "ExpressionNode.h"

class InputCommand :
    public Command

{
public:

    InputCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string INPUT_COMMAND_NAME;

    std::unique_ptr<ExpressionNode> expression;
};
