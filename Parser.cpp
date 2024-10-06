#include "Parser.h"

#include "ArrayNode.h"
#include "ClsCommand.h"
#include "DimCommand.h"
#include "ForCommand.h"
#include "GosubCommand.h"
#include "GotoCommand.h"
#include "IfCommand.h"
#include "LetCommand.h"
#include "ListCommand.h"
#include "MultiCommand.h"
#include "NewCommand.h"
#include "NextCommand.h"
#include "NoOpCommand.h"
#include "NullNode.h"
#include "OperatorNode.h"
#include "PrintCommand.h"
#include "ReturnCommand.h"
#include "RunCommand.h"
#include "StopCommand.h"
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

	auto isColon = [](Lexeme l) { return l.value == ":"; };

	std::vector<Lexeme>::const_iterator colonIter =
		std::find_if(lexStart, lexemes.cend(), isColon);

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
				colonIter = std::find_if(lexStart, lexemes.cend(), isColon);
			}
			else {
				// We've parsed the last command and can exit the loop.
				lexStart = lexemes.cend();
			}
		}

		return multiCommand;
	}

	// Parse the command.

	const std::string& id = (*lexStart).value;

	lexStart++;

	if (id == "CLS") {
		return std::make_unique<ClsCommand>(lexemes);
	}
	else if (id == "DIM") {
		
		if (lexStart == lexemes.cend()) {
			return std::make_unique<DimCommand>(lexemes, "", std::make_unique<NullNode>());
		}

		if ((*lexStart).tokenName != ID) {
			throw ParseException("ID required for DIM!");
		}

		std::string arrayName = (*lexStart).value;

		lexStart++;

		if (lexStart == lexemes.cend()) {
			throw ParseException("Parenthesis required for DIM array size!");
		}

		if ((*lexStart).value == "()") {
			throw ParseException("Expression required for DIM array size!");
		}

		if ((*lexStart).value != "(") {
			throw ParseException("Parenthesis required for DIM array size!");
		}

		lexStart++;

		std::vector<Lexeme>::const_iterator closeParenIter =
			std::find_if(lexStart, lexemes.cend(),
				[](Lexeme l) { return l.value == ")"; });

		if (closeParenIter == lexemes.cend()) {
			throw ParseException("Close parenthesis required for DIM array size!");
		}

		return std::make_unique<DimCommand>(lexemes, arrayName, parseExpression(lexStart, closeParenIter));
	}
	else if (id == "FOR") {

		// FOR (var name) = (expr1) to (expr2)
		// FOR (initExpr) TO (toExpr)

		if (lexStart == lexemes.cend()) {
			return std::make_unique<ForCommand>(lexemes, std::make_unique<NullNode>(), std::make_unique<NullNode>());
		}

		std::vector<Lexeme>::const_iterator toIter =
			std::find_if(lexemes.cbegin(), lexemes.cend(),
				[](Lexeme l) { return l.value == "TO"; });

		if (toIter == lexemes.cend()) {
			throw ParseException("FOR missing TO!");
		}

		std::unique_ptr<ExpressionNode> initExpr = parseExpression(lexemes.cbegin(), toIter);
		std::unique_ptr<ExpressionNode> toExpr = parseExpression(toIter + 1, lexemes.cend());

		return std::make_unique<ForCommand>(lexemes, move(initExpr), move(toExpr));
	}
	else if (id == "GOSUB") {
		return std::make_unique<GosubCommand>(lexemes, parseExpression(lexStart, lexemes.cend()));
	}
	else if (id == "GOTO") {
		return std::make_unique<GotoCommand>(lexemes, parseExpression(lexStart, lexemes.cend()));
	}
	else if (id == "IF") {

		// IF (expr1) THEN (command) (expr2)

		std::vector<Lexeme>::const_iterator thenIter =
			std::find_if(lexemes.cbegin(), lexemes.cend(), 
				[](Lexeme l) { return l.value == "THEN"; });

		if (thenIter == lexemes.cend()) {
			throw ParseException("IF without THEN not allowed!");
		}

		std::unique_ptr<ExpressionNode> expr1 = parseExpression(lexemes.cbegin(), thenIter);
		std::unique_ptr<Command> thenCommand = parseCommand(lexemes, thenIter + 1);

		return std::make_unique<IfCommand>(lexemes, move(expr1), move(thenCommand));
	}
	else if (id == "LET") {
		return std::make_unique<LetCommand>(lexemes, parseExpression(lexStart, lexemes.cend()));
	}
	else if (id == "LIST") {
		return std::make_unique<ListCommand>(lexemes);
	}
	else if (id == "NEW") {
		return std::make_unique<NewCommand>(lexemes);
	}
	else if (id == "NEXT") {
		if (lexStart == lexemes.cend() || (*lexStart).tokenName != ID) {
			throw ParseException("ID required for NEXT!");
		}
		return std::make_unique<NextCommand>(lexemes, (*lexStart).value);
	}
	else if (id == "PRINT") {
		return std::make_unique<PrintCommand>(lexemes, parseExpression(lexStart, lexemes.cend()));
	}
	else if (id == "REM") {
		return std::make_unique<NoOpCommand>(lexemes);
	}
	else if (id == "RETURN") {
		return std::make_unique<ReturnCommand>(lexemes);
	}
	else if (id == "RUN") {
		return std::make_unique<RunCommand>(lexemes);
	}
	else if (id == "STOP") {
		return std::make_unique<StopCommand>(lexemes);
	}
	
	throw ParseException("Parsing error, unknown id " + id + ".");
}

std::unique_ptr<ExpressionNode> Parser::parseExpression(std::vector<Lexeme>::const_iterator lexStart, std::vector<Lexeme>::const_iterator lexEnd)
{
	if (lexStart == lexEnd) {
		// There isn't an expression! This might not be valid for some
		// command types.
		return std::make_unique<NullNode>();
	}

	std::stack<std::unique_ptr<OperatorNode>> operators;
	std::stack<std::unique_ptr<ExpressionNode>> values;

	for (; lexStart != lexEnd; lexStart++) {
		if ((*lexStart).tokenName == INTEGER || (*lexStart).tokenName == STRING) {
			std::unique_ptr<ValueNode> valNode = std::make_unique<ValueNode>(*lexStart);
			values.push(std::move(valNode));
		}
		else if ((*lexStart).tokenName == ID) {

			//  Look ahead to see whether this is an Array.
			if ((lexStart + 1) != lexEnd && (*(lexStart + 1)).value == "(") {
				// This is an array id and subscript. Look forward
				// to find the matching parenthesis and create an
				// expression.
				std::vector<Lexeme>::const_iterator closeParenIter =
					std::find_if(lexStart, lexEnd,
						[](Lexeme l) { return l.value == ")"; });

				if (closeParenIter != lexEnd) {
					std::unique_ptr<ExpressionNode> subscriptExpr = parseExpression(lexStart + 2, closeParenIter);
					std::unique_ptr<ArrayNode> arrayNode = std::make_unique<ArrayNode>(*lexStart, std::move(subscriptExpr));
					values.push(std::move(arrayNode));
					lexStart = closeParenIter;
				}
				else {
					throw ParseException("Parsing error, cannot find closing parenthesis!");
				}
			}
			else {
				std::unique_ptr<VariableNode> varNode = std::make_unique<VariableNode>(*lexStart);
				values.push(std::move(varNode));
			}
		}
		else if ((*lexStart).tokenName == OPERATOR) {
			std::unique_ptr<OperatorNode> opNode = std::make_unique<OperatorNode>(*lexStart);
			operators.push(std::move(opNode));
		}
		else {
			values.push(std::make_unique<NullNode>());
		}
	}

	if (values.empty()) {
		throw ParseException("Parsing error, did not parse any values!");
	}

	// Seed current node with the first value.

	std::unique_ptr<ExpressionNode> currentNode = std::move(values.top());
	values.pop();

	std::stack<std::unique_ptr<OperatorNode>> lowerPrecedence;

	while (operators.size() > 0) {
		std::unique_ptr<OperatorNode> opNode = std::move(operators.top());
		operators.pop();

		// If this node is lower precedence than the next one in the stack
		// hook up the right side and push it on the stack.

		// TODO: Add better precedence logic.
		if (opNode->lexeme.value == "+"
			&& !operators.empty()
			&& operators.top()->lexeme.value == "*") {

			opNode->right = std::move(currentNode);
			lowerPrecedence.push(std::move(opNode));

			// Repopulate current node with the next value.
			currentNode = std::move(values.top());
			values.pop();
		}
		else {
			opNode->right = std::move(currentNode);

			if (values.empty()) {
				throw ParseException("Parsing error, not enough values for operator!");
			}
			
			// Also populate the left side.
			opNode->left = std::move(values.top());
			values.pop();

			// If there is a lower precedence node, set this node to the left side.
			if (!lowerPrecedence.empty()) {
				lowerPrecedence.top()->left = std::move(opNode);
				opNode = std::move(lowerPrecedence.top());
				lowerPrecedence.pop();
			}

			currentNode = std::move(opNode);
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
