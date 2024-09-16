#include "VariableNode.h"

VariableNode::VariableNode(const Lexeme& lexeme) : ExpressionNode(lexeme, VARIABLE_NODE), name(lexeme.value)
{
}

Variable VariableNode::getVariable()
{
    if (lexeme.tokenName == ID) {

        if (runtime.hasVariable(name)) {
            return runtime.getVariable(name);
        }
        else {
            throw ExpressionException("No variable with this name exists!");
        }
    }
    else {
        // A variable node really needs to have an id!
        throw ExpressionException("A variable must be named!");
    }
}

Value VariableNode::eval()
{
    return getVariable().value;
}

bool VariableNode::evalBool()
{
    return getVariable().value.evalBool();
}

void VariableNode::print()
{
    runtime << "VariableNode: " << lexeme.value << std::endl;
}
