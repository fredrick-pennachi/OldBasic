#pragma once

#include <ostream>
#include <string>

class Value
{
public:
	enum ValueType { NONE, INTEGER, STRING };

	Value();

	Value(int intValue);

	Value(std::string strValue);

	ValueType type;

	int intValue;

	std::string strValue;
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
