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
    else if (lexeme.value == ";") {
        return Value::concat(left->eval(), right->eval());
    }
    else if (lexeme.value == "=") {
        throw ExpressionException("Assignment must be evaluated using LET command!");
    }

    return Value();
}

bool OperatorNode::evalBool()
{
    Value lhs = left->eval();
    Value rhs = right->eval();

    if (lhs.getType() != ValueType::INTEGER || rhs.getType() != ValueType::INTEGER) {
        throw ExpressionException("Cannot evaluate non-integer arguments as bool!");
    }

    if (lexeme.value == "<") {
        return lhs.intValue < rhs.intValue;
    }
    else if (lexeme.value == "<=") {
        return lhs.intValue <= rhs.intValue;
    }
    else if (lexeme.value == ">") {
        return lhs.intValue > rhs.intValue;
    }
    else if (lexeme.value == ">=") {
        return lhs.intValue >= rhs.intValue;
    }
    else if (lexeme.value == "<>") {
        return lhs.intValue != rhs.intValue;
    }
    else if (lexeme.value == "=") {
        return lhs.intValue == rhs.intValue;
    }
    else {
        throw ExpressionException("Unknown operator used in boolean evaluation!");
    }
}

void OperatorNode::print()
{
    runtime << "OperatorNode: " << lexeme.value << std::endl;
    runtime << "LeftHandSide" << std::endl;
    runtime << "\\_ ";
    left->print();
    runtime << "RightHandSide" << std::endl;
    runtime << "\\_ ";
    right->print();
}
