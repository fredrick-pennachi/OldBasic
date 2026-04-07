
#include "SleepCommand.h"

#include <iostream>

const std::string SleepCommand::SLEEP_COMMAND_NAME = "SLEEP";

SleepCommand::SleepCommand(const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(SLEEP_COMMAND_NAME, lexemes), expression(move(expression))
{
}

CommandStatus SleepCommand::invoke()
{
	runtime.sleep(expression->eval().intValue);

	return OK;
}
