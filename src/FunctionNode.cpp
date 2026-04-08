// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "FunctionNode.h"

#include <algorithm>
#include <cmath>

const std::array<const std::string, 10> FunctionNode::functionNames = {
    "RND", "INT", "ATN", "ABS", "SQR", "INKEY$", "CHR$", "SIN", "COS", "TAN"};

std::default_random_engine FunctionNode::generator = std::default_random_engine((unsigned int)time(nullptr));
std::uniform_real_distribution<double> FunctionNode::distribution = std::uniform_real_distribution<double>(0.0, 1.0);

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
    else if (name == "ATN") {
        if (argument != nullptr) {
            Value val = argument->eval();
            if (val.getType() == ValueType::DBL_FLOAT) {
                return Value(atan(val.floatValue));
            }
            else if (val.getType() == ValueType::INTEGER) {
                return Value(atan((double)val.intValue));
            }
            else {
                throw ExpressionException("Cannot use non-numeric Value with ATN!");
            }
        }
        
        return Value(atan(0.0));
    }
    else if (name == "ABS") {
        if (argument != nullptr) {
            Value val = argument->eval();
            if (val.getType() == ValueType::DBL_FLOAT) {
                return Value(abs(val.floatValue));
            }
            else if (val.getType() == ValueType::INTEGER) {
                return Value(abs((double)val.intValue));
            }
            else {
                throw ExpressionException("Cannot use non-numeric Value with ABS!");
            }
        }

        return Value(abs(0.0));
    }
    else if (name == "SQR") {
        if (argument != nullptr) {
            Value val = argument->eval();
            if (val.getType() == ValueType::DBL_FLOAT) {
                return Value(sqrt(val.floatValue));
            }
            else if (val.getType() == ValueType::INTEGER) {
                return Value(sqrt((double)val.intValue));
            }
            else {
                throw ExpressionException("Cannot use non-numeric Value with SQR!");
            }
        }

        return Value(abs(0.0));
    }
    else if (name == "INKEY$") {
        return Value(runtime.getInkeyInput());
    }
    else if (name == "CHR$") {

        if (argument != nullptr) {
            Value val = argument->eval();
            if (val.getType() != ValueType::INTEGER) {
                throw ExpressionException("Cannot use CHR$ with non-integer argument!");
            }

            return Value(std::string(1, (char) val.intValue));
        }
        else {
            throw ExpressionException("Cannot use CHR$ without argument!");
        }
    }
    else if (name == "SIN") {
        if (argument != nullptr) {
            Value val = argument->eval();
            if (val.getType() == ValueType::DBL_FLOAT) {
                return Value(sin(val.floatValue));
            }
            else if (val.getType() == ValueType::INTEGER) {
                return Value(sin((double)val.intValue));
            }
            else {
                throw ExpressionException("Cannot use non-numeric Value with SIN!");
            }
        }

        return Value(sin(0.0));
    }
    else if (name == "COS") {
        if (argument != nullptr) {
            Value val = argument->eval();
            if (val.getType() == ValueType::DBL_FLOAT) {
                return Value(cos(val.floatValue));
            }
            else if (val.getType() == ValueType::INTEGER) {
                return Value(cos((double)val.intValue));
            }
            else {
                throw ExpressionException("Cannot use non-numeric Value with COS!");
            }
        }

        return Value(cos(0.0));
    }
    else if (name == "TAN") {
        if (argument != nullptr) {
            Value val = argument->eval();
            if (val.getType() == ValueType::DBL_FLOAT) {
                return Value(tan(val.floatValue));
            }
            else if (val.getType() == ValueType::INTEGER) {
                return Value(tan((double)val.intValue));
            }
            else {
                throw ExpressionException("Cannot use non-numeric Value with TAN!");
            }
        }

        return Value(tan(0.0));
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
