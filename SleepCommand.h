
#pragma once
#include "Command.h"
#include "ExpressionNode.h"

class SleepCommand :
    public Command

{
public:

    SleepCommand(const std::vector<Lexeme>& lexemes,
        std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    CommandStatus invoke() override;

    static const std::string SLEEP_COMMAND_NAME;

    std::unique_ptr<ExpressionNode> expression;
};
