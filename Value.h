#pragma once

#include <ostream>
#include <string>

using namespace std;

class Value
{
public:
	enum ValueType { NONE, INTEGER, STRING };

	Value();

	Value(int intValue);

	Value(string strValue);

	ValueType type;

	int intValue;

	string strValue;
};

Value operator*(const Value& lhs, const Value& rhs);
Value operator/(const Value& lhs, const Value& rhs);
Value operator+(const Value& lhs, const Value& rhs);
Value operator-(const Value& lhs, const Value& rhs);

ostream& operator<<(ostream& stream, const Value& value);

class InvalidOperatorExeption : public runtime_error {
public:
	InvalidOperatorExeption(string what);
};
