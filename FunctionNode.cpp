#include "FunctionNode.h"

#include <algorithm>
#include <random>

const std::array<const std::string, 2> FunctionNode::functionNames = { "RND", "INT" };

FunctionNode::FunctionNode(const Lexeme& lexeme, std::unique_ptr<ExpressionNode> argument)
    : ExpressionNode(lexeme, FUNCTION_NODE), argument(std::move(argument))
{
    if (lexeme.tokenName == ID) {
        // Retrieve the name of this function.
        this->name = lexeme.value;
    }
    else {
        // An array expression really needs to have an id!
        throw ExpressionException("A function expression must be named!");
    }
}

bool FunctionNode::isFunction(const std::string& id)
{
    auto it = find(functionNames.cbegin(), functionNames.cend(), id);

    return it != functionNames.cend();
}

Value FunctionNode::eval()
{
    if (name == "RND") {
        std::default_random_engine generator(time(nullptr));
        std::uniform_real_distribution<double> distribution(0.0, 1.0);
        return Value(distribution(generator));
    }
    else if (name == "INT") {
        if (argument != nullptr) {
            Value val = argument->eval();
            if (val.getType() == ValueType::DBL_FLOAT) {
                return Value((int)val.floatValue);
            }
            else if (val.getType() == ValueType::INTEGER) {
                return val;
            }
            else {
                throw ExpressionException("Cannot cast non-numeric Value to INT!");
            }
        }
        else {
            return Value(0);
        }
    }

    if (argument != nullptr) {
        return argument->eval();
    }
    else {
        return Value(0);
    }
}

bool FunctionNode::evalBool()
{
    return eval().evalBool();
}

void FunctionNode::print()
{
    runtime << "FunctionNode: " << name
        << "(" << argument->eval() << ")" << std::endl;
}
