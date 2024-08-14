#include "IfCommand.h"

const std::string IfCommand::IF_COMMAND_NAME = "IF";

IfCommand::IfCommand(
	const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression,
	std::unique_ptr<Command> command)
	: Command(IF_COMMAND_NAME, lexemes), expression(move(expression)), command(move(command))
{
}

int IfCommand::invoke()
{
	if (expression->evalBool()) {
		command->invoke();
	}

    return 0;
}
