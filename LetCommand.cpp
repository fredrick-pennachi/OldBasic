#include "ArrayNode.h"
#include "LetCommand.h"
#include "OperatorNode.h"
#include "ValueNode.h"
#include "VariableNode.h"

#include <sstream>

const std::string LetCommand::LET_COMMAND_NAME = "LET";

LetCommand::LetCommand(
	const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> expression)
	: Command(LET_COMMAND_NAME, lexemes)
{
	if (expression->nodeType == ExpressionNode::NULL_NODE) {
		// No expression, leave assignExpr unset.
		return;
	}
	else if (expression->nodeType == ExpressionNode::OPERATOR_NODE
		&& expression->lexeme.value == "=") {

		OperatorNode* opNode = dynamic_cast<OperatorNode*>(expression.get());

		if (opNode != nullptr) {
			assignExpr = std::unique_ptr<OperatorNode>(opNode);
		}

		if (assignExpr &&
			assignExpr->left->nodeType == ExpressionNode::VARIABLE_NODE ||
			assignExpr->left->nodeType == ExpressionNode::ARRAY_NODE) {

			expression.release();
			return;
		}
	}

	throw InvalidSyntaxException("LET command requires an assignment expression!");
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
	if (assignExpr) {

		if (assignExpr->left->nodeType == ExpressionNode::VARIABLE_NODE) {
			VariableNode* varNode = dynamic_cast<VariableNode*>(assignExpr->left.get());

			if (varNode) {
				Value value = assignExpr->right->eval();

				Variable variable(varNode->name, value);

				runtime.setVariable(variable);
			}
		}
		else if (assignExpr->left->nodeType == ExpressionNode::ARRAY_NODE) {
			ArrayNode* arrNode = dynamic_cast<ArrayNode*>(assignExpr->left.get());

			if (arrNode) {
				Value value = assignExpr->right->eval();

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
