#pragma once

#include "Variable.h"
#include "ValueType.h"

#include <ostream>
#include <string>

class Value
{
public:

	Value();

	Value(int intValue);

	Value(std::string strValue);

	Value(Variable var);

	ValueType::Enum getType() const;

	bool isVariable() const;

	int intValue;

	std::string strValue;

	Variable var;

protected:
	ValueType::Enum valueType;

};

Value operator*(const Value& lhs, const Value& rhs);
Value operator/(const Value& lhs, const Value& rhs);
Value operator+(const Value& lhs, const Value& rhs);
Value operator-(const Value& lhs, const Value& rhs);

std::ostream& operator<<(std::ostream& stream, const Value& value);

class InvalidOperatorExeption : public std::runtime_error {
public:
	InvalidOperatorExeption(std::string what);
};
