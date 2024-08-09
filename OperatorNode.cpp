#include "OperatorNode.h"

OperatorNode::OperatorNode(
    const Lexeme& lexeme) :
        ExpressionNode(lexeme, OPERATOR_NODE)
{
}

Value OperatorNode::eval()
{
    if (lexeme.value == "*") {
        return left->eval() * right->eval();
    }
    else if (lexeme.value == "/") {
        return left->eval() / right->eval();
    }
    else if (lexeme.value == "+") {
        return left->eval() + right->eval();
    }
    else if (lexeme.value == "-") {
        return left->eval() - right->eval();
    }
    else if (lexeme.value == "=") {

        Value lhs = left->eval();
        if (!lhs.isVariable()) {
            throw ExpressionException("Assignment operator requires a variable on left hand side!");
        }

        Value rhs = right->eval();

        if (rhs.getType() == ValueType::INTEGER) {
            lhs.var.valueType = ValueType::INTEGER;
            lhs.intValue = rhs.intValue;
        }
        else if (rhs.getType() == ValueType::STRING) {
            lhs.var.valueType = ValueType::STRING;
            lhs.strValue = rhs.strValue;
        }
        else {
            throw ExpressionException("Assignment operator requires a primitive value on right hand side!");
        }

        return lhs;
    }

    return Value();
}
