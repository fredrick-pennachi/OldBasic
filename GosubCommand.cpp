#include "GosubCommand.h"

const std::string GosubCommand::GOSUB_COMMAND_NAME = "GOSUB";

GosubCommand::GosubCommand(const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(GOSUB_COMMAND_NAME, lexemes), expression(move(expression))
{
}

int GosubCommand::invoke()
{
	runtime.setGosub(expression->eval().intValue);
	return 0;
}
