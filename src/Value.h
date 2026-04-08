/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "ValueType.h"

#include <ostream>
#include <string>

class Value
{
public:
	static const double FLOAT_EPSILON;

	Value();

	Value(int intValue);

	Value(std::string strValue);

	Value(double floatValue);

	static Value concat(const Value& lhs, const Value& rhs);

	ValueType::Enum getType() const;

	bool evalBool() const;

	int intValue;

	std::string strValue;

	double floatValue;

protected:
	ValueType::Enum valueType;
};

Value operator*(const Value& lhs, const Value& rhs);
Value operator/(const Value& lhs, const Value& rhs);
Value operator+(const Value& lhs, const Value& rhs);
Value operator-(const Value& lhs, const Value& rhs);

bool operator<(const Value& lhs, const Value& rhs);
bool operator<=(const Value& lhs, const Value& rhs);
bool operator>(const Value& lhs, const Value& rhs);
bool operator>=(const Value& lhs, const Value& rhs);
bool operator==(const Value& lhs, const Value& rhs);
bool operator!=(const Value& lhs, const Value& rhs);

std::ostream& operator<<(std::ostream& stream, const Value& value);

class InvalidOperatorExeption : public std::runtime_error {
public:
	InvalidOperatorExeption(std::string what);
};
