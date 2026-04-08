// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Array.h"

Array::Array() : capacity(1)
{
	values.push_back(Value(0));
}

Array::Array(int capacity) : capacity(capacity)
{
	for (int i = 0; i < capacity; i++) {
		values.push_back(Value(0));
	}
}

Value Array::getValue(int subscript) const
{
	if (subscript < 1) {
		throw ArrayIndexException("Array index starts at 1.");
	}
	else if (subscript > capacity) {
		throw ArrayIndexException("Array index out of bounds.");
	}
	else {
		return values.at(subscript - 1);
	}
}

void Array::putValue(int subscript, Value value)
{
	if (subscript < 1) {
		throw ArrayIndexException("Array index starts at 1.");
	}
	else if (subscript > capacity) {
		throw ArrayIndexException("Array index out of bounds.");
	}
	else {
		values[subscript - 1] = value;
	}
}

int Array::getSize() const
{
	return (int) values.size();
}

std::ostream& operator<<(std::ostream& stream, const Array& array)
{
	for (int i = 1; i <= array.getSize(); i++)
	{
		stream << array.getValue(i);

		if (i < array.getSize()) {
			stream << ", ";
		}
	}

	return stream;
}

ArrayIndexException::ArrayIndexException(std::string what) : runtime_error(what)
{
}
