#include "GosubCommand.h"

const std::string GosubCommand::GOSUB_COMMAND_NAME = "GOSUB";

GosubCommand::GosubCommand(const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(GOSUB_COMMAND_NAME, lexemes), expression(move(expression))
{
}

int GosubCommand::invoke()
{
	if (!runtime.isReturn) {
		runtime.setGosub(expression->eval().intValue);
		return 2;
	}
	else {
		// This is a return to the gosub so don't jump again.
		runtime.isReturn = false;
		return 0;
	}	
}
