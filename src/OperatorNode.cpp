#include "OperatorNode.h"

std::map<std::string, int> OperatorNode::Precedence = {
    {"*", 40},
    {"/", 40},
    {"+", 30},
    {"-", 30},
    {";", 25},
    {"<", 15},
    {"<=", 15},
    {">", 15},
    {">=", 15},
    {"=", 10},
    {"<>", 10},
};

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
    else if (lexeme.value == "AND" || lexeme.value == "OR") {
        if (evalBool()) {
            return Value("TRUE");
        }
        else {
            return Value("FALSE");
        }
    }

    return Value();
}

bool OperatorNode::evalBool()
{
    if (lexeme.value == "AND" || lexeme.value == "OR") {
        bool lhs = left->evalBool();
        bool rhs = right->evalBool();
        
        if (lexeme.value == "AND") {
            return lhs && rhs;
        }
        else {
            return lhs || rhs;
        }
    }

    Value lhs = left->eval();
    Value rhs = right->eval();

    if (lexeme.value == "<") {
        return lhs < rhs;
    }
    else if (lexeme.value == "<=") {
        return lhs <= rhs;
    }
    else if (lexeme.value == ">") {
        return lhs > rhs;
    }
    else if (lexeme.value == ">=") {
        return lhs >= rhs;
    }
    else if (lexeme.value == "<>") {
        return lhs != rhs;
    }
    else if (lexeme.value == "=") {
        return lhs == rhs;
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

int OperatorNode::getPrecendence()
{
    if (Precedence.count(lexeme.value) > 0)
    {
        return Precedence[lexeme.value];
    }
    else {
        return 0;
    }
}
