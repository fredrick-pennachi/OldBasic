#include "ForCommand.h"
#include "VariableNode.h"

#include <sstream>

const std::string ForCommand::FOR_COMMAND_NAME = "FOR";

ForCommand::ForCommand(const std::vector<Lexeme>& lexemes,
	std::unique_ptr<ExpressionNode> initExpr,
	std::unique_ptr<ExpressionNode> toExpr)
	: Command(FOR_COMMAND_NAME, lexemes)
{
	if (initExpr->nodeType == ExpressionNode::NULL_NODE &&
		toExpr->nodeType == ExpressionNode::NULL_NODE) {
		// No expressions, command will only print forLoops map.
		return;
	}
	if (initExpr->nodeType == ExpressionNode::OPERATOR_NODE
		&& initExpr->lexeme.value == "=") {

		OperatorNode* opNode = dynamic_cast<OperatorNode*>(initExpr.get());

		if (opNode != nullptr) {
			this->initExpr = std::unique_ptr<OperatorNode>(opNode);
		}

		if (toExpr) {
			this->toExpr = move(toExpr);
		}

		if (opNode &&
			opNode->left->nodeType == ExpressionNode::VARIABLE_NODE &&
			this->toExpr) {
			initExpr.release();
			toExpr.release();

			return;
		}
	}

	throw InvalidSyntaxException("FOR command requires initialization and condition expressions!");
}

CommandStatus ForCommand::invoke()
{
	// If this FOR loop is already in progress then
	// increment by STEP (not added yet) and continue
	// otherwise initialize new FOR loop in the runtime.
	// NEXT should handle the test about whether to loop
	// or not. reset() will be called by NEXT when the
	// loop is finished.

	if (varName != "") {
		Variable& controlVar = runtime.getVariable(varName);
		controlVar.value = controlVar.value + 1;
	}
	else if (initExpr) {

		if (initExpr->left->nodeType == ExpressionNode::VARIABLE_NODE) {
			VariableNode* varNode = dynamic_cast<VariableNode*>(initExpr->left.get());

			if (varNode) {

				Value value = initExpr->right->eval();

				varName = varNode->name;

				runtime.setForLoop(Variable(varName, value));
			}
		}
	}
	else {
		// No expression, print the forLoops map.
		std::map<std::string, int>::const_iterator iter = runtime.forLoops.cbegin();

		runtime << "FOR Loops:" << std::endl << "VAR: LINE" << std::endl;

		for (; iter != runtime.forLoops.cend(); iter++) {
			runtime << iter->first << ": " << iter->second << std::endl;
		}
	}

	return OK;
}

int ForCommand::reset()
{
	runtime.forLoops.erase(varName);
	runtime.variables.erase(varName);
	varName = "";

	return OK;
}

