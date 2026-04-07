#include "ExpressionNode.h"

ExpressionNode::ExpressionNode(const Lexeme& lexeme, NodeType nodeType)
	: lexeme(lexeme), nodeType(nodeType)
{
}

ExpressionException::ExpressionException(std::string what) : runtime_error(what)
{
}
