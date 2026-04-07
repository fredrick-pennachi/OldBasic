#pragma once

#include "Value.h"

#include <string>

class Variable
{
public:
	Variable();

	Variable(const std::string& name, Value value);

	std::string name;

	Value value;
};

std::ostream& operator<<(std::ostream& stream, const Variable& value);
