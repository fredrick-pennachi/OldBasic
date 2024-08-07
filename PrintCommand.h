#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#include <string>

class PrintCommand : public Command {
public:
    PrintCommand(const std::vector<Lexeme>& lexemes, std::unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    int invoke() override;

    static const std::string PRINT_COMMAND_NAME;

    std::unique_ptr<ExpressionNode> expression;
};

