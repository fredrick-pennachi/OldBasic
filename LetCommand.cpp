#include "ArrayNode.h"
#include "LetCommand.h"
#include "OperatorNode.h"
#include "NullNode.h"
#include "ValueNode.h"
#include "VariableNode.h"

#include <sstream>

const std::string LetCommand::LET_COMMAND_NAME = "LET";

LetCommand::LetCommand(
	const std::vector<Lexeme>& lexemes)
	: Command(LET_COMMAND_NAME, lexemes)
{
	// No expression, set members to NullNodes.
	this->variable = std::make_unique<NullNode>();
	this->expression = std::make_unique<NullNode>();
}

LetCommand::LetCommand(
	const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> variable,
	std::unique_ptr<ExpressionNode> expression)
	: Command(LET_COMMAND_NAME, lexemes)
{
	if (variable->nodeType != ExpressionNode::NULL_NODE &&
		variable->nodeType != ExpressionNode::VARIABLE_NODE &&
		variable->nodeType != ExpressionNode::ARRAY_NODE) {
		throw InvalidSyntaxException("LET command variable must be VARIABLE or ARRAY!");
	}

	this->variable = std::move(variable);
	this->expression = std::move(expression);
}

/*

Forms of LET:

LET A = 1
LET B$ = "B"
LET A = A + 1
LET ARR(1) = A

*/

CommandStatus LetCommand::invoke()
{
	if (variable->nodeType != ExpressionNode::NULL_NODE) {

		if (variable->nodeType == ExpressionNode::VARIABLE_NODE) {
			VariableNode* varNode = dynamic_cast<VariableNode*>(variable.get());

			if (varNode) {
				Value value = expression->eval();

				Variable variable(varNode->name, value);

				runtime.setVariable(variable);
			}
		}
		else if (variable->nodeType == ExpressionNode::ARRAY_NODE) {
			ArrayNode* arrNode = dynamic_cast<ArrayNode*>(variable.get());

			if (arrNode) {
				Value value = expression->eval();

				runtime.setArrayValue(arrNode->name,
					arrNode->subscript->eval().intValue, value);
			}
		}
		else {
			std::stringstream ss;
			ss << (*this);
			throw InvalidSyntaxException("Unsupported assignment: \"" + ss.str() + "\"");
		}
	}
	else {
		// No expression, print all the variables.
		std::map<std::string, Variable>::const_iterator iter = runtime.variables.cbegin();

		runtime << "Variables:" << std::endl;

		for (; iter != runtime.variables.cend(); iter++) {

			runtime << iter->second << std::endl;
		}
	}
	
	return OK;
}
