#pragma once

#include "Command.h"
#include "ExpressionNode.h"

#include <string>

class PrintCommand : public Command {
public:
    PrintCommand(const vector<Lexeme>& lexemes, unique_ptr<ExpressionNode> expression);

    // Inherited via Command
    int invoke(Runtime& runtime) override;

    static const string PRINT_COMMAND_NAME;

    unique_ptr<ExpressionNode> expression;
};

