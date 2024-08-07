#include "Parser.h"

#include "GotoCommand.h"
#include "LetCommand.h"
#include "ListCommand.h"
#include "NoOpCommand.h"
#include "NullNode.h"
#include "OperatorNode.h"
#include "PrintCommand.h"
#include "RunCommand.h"
#include "ValueNode.h"
#include "VariableNode.h"

#include <stack>

std::unique_ptr<Command> Parser::parse(const std::vector<Lexeme>& lexemes) {

	if (lexemes.empty()) {
		// Not sure how the program would get here.
		return std::make_unique<NoOpCommand>(lexemes);
	}

	int currentIndex = 0;

	if (lexemes[currentIndex].tokenName == INTEGER) {
		if (lexemes.size() == 1) {
			return std::make_unique<NoOpCommand>(lexemes);
		}
		else {
			// Skip past the line number.
			currentIndex++;
		}
	}

	TokenName tokenName = lexemes[currentIndex].tokenName;
	// Only ID should be valid in this position.
	if (tokenName == ID) {
		return parseId(lexemes, currentIndex);
	}
	else {
		throw ParseException("Parsing error, unexpected token " + TokenNameMap.at(tokenName) + ".");
	}
}

std::unique_ptr<Command> Parser::parseId(const std::vector<Lexeme>& lexemes, int index)
{
	const std::string& id = lexemes[index].value;

	// Is this a command?

	// Maybe this logic should be tidied up with sets of commands and functions.
	if (id == "PRINT") {
		return std::make_unique<PrintCommand>(lexemes, parseExpression(lexemes));
	}
	else if (id == "GOTO") {
		return std::make_unique<GotoCommand>(lexemes);
	}
	else if (id == "LET") {
		return std::make_unique<LetCommand>(lexemes, parseExpression(lexemes));
	}
	else if (id == "LIST") {
		return std::make_unique<ListCommand>(lexemes);
	}
	else if (id == "RUN") {
		return std::make_unique<RunCommand>(lexemes);
	}

	// Add else for if it is an existing variable.

	throw ParseException("Parsing error, unknown id " + id + ".");
}

std::unique_ptr<ExpressionNode> Parser::parseExpression(const std::vector<Lexeme>& lexemes)
{
	int i = 0;

	// Skip over the first lexeme if it's a line number.
	if (lexemes[i].tokenName == INTEGER) {
		i++;
	}

	// Skip over the LET id.
	i++;

	if (i == lexemes.size()) {
		// There isn't an expression! This might not be valid for some
		// command types.
		return std::make_unique<NullNode>();
	}

	std::stack<Lexeme> operators;
	std::stack<Lexeme> values;

	for (; i < lexemes.size(); i++) {
		if (lexemes[i].tokenName == OPERATOR) {
			operators.push(lexemes[i]);
		}
		else {
			values.push(lexemes[i]);
		}
	}

	if (values.empty()) {
		throw ParseException("Parsing error, did not parse any values!");
	}

	Lexeme value = values.top();
	values.pop();

	// Seed current node with the first value.

	std::unique_ptr<ExpressionNode> currentNode;

	if (value.tokenName == INTEGER || value.tokenName == STRING) {
		currentNode = std::make_unique<ValueNode>(value);
	}
	else if (value.tokenName == ID) {
		currentNode = std::make_unique<VariableNode>(value);
	}

	std::stack<std::unique_ptr<OperatorNode>> lowerPrecedence;

	while (operators.size() > 0) {
		Lexeme op = operators.top();
		std::unique_ptr<OperatorNode> opNode = std::make_unique<OperatorNode>(op);
		operators.pop();

		// If this node is lower precendence than the next one in the stack
		// hook up the right side and push it on the stack.

		if (op.value == "+" && !operators.empty() && operators.top().value == "*") {
			opNode->right = move(currentNode);
			lowerPrecedence.push(move(opNode));

			// Repopulate current node with the next value.
			Lexeme value = values.top();
			values.pop();
			
			if (value.tokenName == INTEGER || value.tokenName == STRING) {
				currentNode = std::make_unique<ValueNode>(value);
			}
			else if (value.tokenName == ID) {
				currentNode = std::make_unique<VariableNode>(value);
			}
		}
		else {
			opNode->right = move(currentNode);
			
			// Also populate the left side.
			Lexeme value = values.top();
			values.pop();

			if (value.tokenName == INTEGER || value.tokenName == STRING) {
				opNode->left = std::make_unique<ValueNode>(value);
			}
			else if (value.tokenName == ID) {
				opNode->left = std::make_unique<VariableNode>(value);
			}

			// If there is a lower precedence node, set this node to the left side.
			if (!lowerPrecedence.empty()) {
				lowerPrecedence.top()->left = move(opNode);
				opNode = move(lowerPrecedence.top());
				lowerPrecedence.pop();
			}

			currentNode = move(opNode);
		}
	}

	return currentNode;
}


std::ostream& operator<<(std::ostream& os, std::stack<Lexeme> stack)
{
	while (!stack.empty())
	{
		os << stack.top().value << " ";
		stack.pop();
	}
	return os; // end of function
}

ParseException::ParseException(const std::string what) : runtime_error(what)
{
}
