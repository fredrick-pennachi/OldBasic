#include "Parser.h"

#include "GotoCommand.h"
#include "IfCommand.h"
#include "LetCommand.h"
#include "ListCommand.h"
#include "MultiCommand.h"
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

	std::vector<Lexeme>::const_iterator lexStart = lexemes.cbegin();

	if ((*lexStart).tokenName == INTEGER) {
		if (lexemes.size() == 1) {
			return std::make_unique<NoOpCommand>(lexemes);
		}
		else {
			// Skip past the line number.
			lexStart++;
		}
	}

	TokenName tokenName = (*lexStart).tokenName;
	// Only ID should be valid in this position.
	if (tokenName == ID) {
		return parseCommand(lexemes, lexStart);
	}
	else {
		throw ParseException("Parsing error, unexpected token " + TokenNameMap.at(tokenName) + ".");
	}
}

std::unique_ptr<Command> Parser::parseCommand(const std::vector<Lexeme>& lexemes, std::vector<Lexeme>::const_iterator lexStart)
{
	// Check if this is a multi command.

	Lexeme colonLexeme;
	colonLexeme.tokenName = SEPARATOR;
	colonLexeme.value = ":";

	std::vector<Lexeme>::const_iterator colonIter =
		std::find(lexStart, lexemes.cend(), colonLexeme);

	if (colonIter != lexemes.cend()) {
		// Create a command for each colon delimited collection...		
		std::unique_ptr<MultiCommand> multiCommand = std::make_unique<MultiCommand>(lexemes);

		while (lexStart != lexemes.cend()) {

			std::vector<Lexeme> delimitedLexemes;

			delimitedLexemes.insert(delimitedLexemes.cbegin(), lexStart, colonIter);

			std::unique_ptr<Command> delimitedCommand = parse(delimitedLexemes);

			multiCommand->commands.push_back(move(delimitedCommand));

			if (colonIter != lexemes.end()) {
				// Skip over the colon to get to the next statement.
				lexStart = colonIter + 1;
				colonIter = std::find(lexStart, lexemes.cend(), colonLexeme);
			}
			else {
				// We've parsed the last command and can exit the loop.
				lexStart = lexemes.cend();
			}
		}

		return multiCommand;
	}

	const std::string& id = (*lexStart).value;

	// Is this a command?

	// Maybe this logic should be tidied up with sets of commands and functions.
	if (id == "PRINT") {
		return std::make_unique<PrintCommand>(lexemes, parseExpression(lexStart, lexemes.cend()));
	}
	else if (id == "GOTO") {
		return std::make_unique<GotoCommand>(lexemes, parseExpression(lexStart, lexemes.cend()));
	}
	else if (id == "LET") {
		return std::make_unique<LetCommand>(lexemes, parseExpression(lexStart, lexemes.cend()));
	}
	else if (id == "LIST") {
		return std::make_unique<ListCommand>(lexemes);
	}
	else if (id == "RUN") {
		return std::make_unique<RunCommand>(lexemes);
	}
	else if (id == "IF") {
		// Break the statement up...
		// IF (expr1)
		// THEN (command) (expr2)

		Lexeme thenLexeme;
		thenLexeme.tokenName = ID;
		thenLexeme.value = "THEN";
		
		std::vector<Lexeme>::const_iterator thenIter =
			std::find(cbegin(lexemes), cend(lexemes), thenLexeme);

		if (thenIter == cend(lexemes)) {
			throw ParseException("IF without THEN not allowed!");
		}

		std::unique_ptr<ExpressionNode> expr1 = parseExpression(cbegin(lexemes), thenIter);
		std::unique_ptr<Command> thenCommand = parseCommand(lexemes, thenIter + 1);

		return std::make_unique<IfCommand>(lexemes, move(expr1), move(thenCommand));
	}

	throw ParseException("Parsing error, unknown id " + id + ".");
}

std::unique_ptr<ExpressionNode> Parser::parseExpression(std::vector<Lexeme>::const_iterator lexStart, std::vector<Lexeme>::const_iterator lexEnd)
{
	// Skip over the first lexeme if it's a line number.
	if ((*lexStart).tokenName == INTEGER) {
		lexStart++;
	}

	// Skip over the Command id.
	lexStart++;

	if (lexStart == lexEnd) {
		// There isn't an expression! This might not be valid for some
		// command types.
		return std::make_unique<NullNode>();
	}

	std::stack<Lexeme> operators;
	std::stack<Lexeme> values;

	for (; lexStart != lexEnd; lexStart++) {
		if ((*lexStart).tokenName == OPERATOR) {
			operators.push(*lexStart);
		}
		else {
			values.push(*lexStart);
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
	else {
		currentNode = std::make_unique<NullNode>();
	}

	std::stack<std::unique_ptr<OperatorNode>> lowerPrecedence;

	while (operators.size() > 0) {
		Lexeme op = operators.top();
		std::unique_ptr<OperatorNode> opNode = std::make_unique<OperatorNode>(op);
		operators.pop();

		// If this node is lower precedence than the next one in the stack
		// hook up the right side and push it on the stack.

		// TODO: Add better precedence logic.
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
			else {
				currentNode = std::make_unique<NullNode>();
			}
		}
		else {
			opNode->right = move(currentNode);

			if (values.empty()) {
				throw ParseException("Parsing error, not enough values for operator!");
			}
			
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
