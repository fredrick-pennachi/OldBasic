// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "OperatorNode.h"
#include "PrintCommand.h"

#include <iostream>
#include <sstream>

const std::string PrintCommand::PRINT_COMMAND_NAME = "PRINT";

PrintCommand::PrintCommand(
	const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(PRINT_COMMAND_NAME, lexemes),
	expression(move(expression))
{
}

/*

Forms of PRINT:

PRINT
PRINT "Hello!"
PRINT HELLO_VARIABLE$
PRINT 2 + 2
PRINT A(1)

*/

CommandStatus PrintCommand::invoke()
{
	if (expression->nodeType != ExpressionNode::NULL_NODE) {

		bool newLine = true;

		if (expression->nodeType == ExpressionNode::OPERATOR_NODE) {
			OperatorNode* opNode = dynamic_cast<OperatorNode*>(expression.get());
			if (opNode && opNode->right->nodeType == ExpressionNode::NULL_NODE) {
				newLine = false;
			}
		}

		Value value = expression->eval();

		if (newLine) {
			runtime << value << std::endl;
		}
		else {
			runtime << value;
		}
	}
	else {
		// No argument, just print a newline.
		runtime << std::endl;
	}

	return OK;
}
