#pragma once

#include "ValueType.h"

#include <ostream>
#include <string>

class Value
{
public:

	Value();

	Value(int intValue);

	Value(std::string strValue);

	ValueType::Enum getType() const;

	bool evalBool() const;

	int intValue;

	std::string strValue;

protected:
	ValueType::Enum valueType;
};

Value operator*(const Value& lhs, const Value& rhs);
Value operator/(const Value& lhs, const Value& rhs);
Value operator+(const Value& lhs, const Value& rhs);
Value operator-(const Value& lhs, const Value& rhs);

bool operator<(const Value& lhs, const Value& rhs);
bool operator<=(const Value& lhs, const Value& rhs);

std::ostream& operator<<(std::ostream& stream, const Value& value);

class InvalidOperatorExeption : public std::runtime_error {
public:
	InvalidOperatorExeption(std::string what);
};
