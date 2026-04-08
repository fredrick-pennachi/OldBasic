/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Value.h"

#include <ostream>
#include <vector>

class Array
{
public:

	Array();

	Array(int capacity);

	Value getValue(int subscript) const;

	void putValue(int subscript, Value value);

	int getSize() const;

	int capacity;

private:

	std::vector<Value> values;
};

std::ostream& operator<<(std::ostream& stream, const Array& array);

class ArrayIndexException : public std::runtime_error {
public:
	ArrayIndexException(std::string what);
};
