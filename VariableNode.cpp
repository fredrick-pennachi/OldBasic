#include "VariableNode.h"

VariableNode::VariableNode(const Lexeme& lexeme) : ExpressionNode(lexeme, VARIABLE_NODE)
{
}

Value VariableNode::eval()
{
    if (lexeme.tokenName == ID) {
        // Retrieve the variable value if it exists.
        std::string& variableName = lexeme.value;
        if (runtime.hasVariable(variableName)) {
            return runtime.getVariable(lexeme.value);
        }
        else {
            Variable var(lexeme.value, ValueType::NONE);
            return Value(var);
        }
    }
    else {
        // A variable node really needs to have an id!
        throw ExpressionException("A variable must be named!");
    }
}
