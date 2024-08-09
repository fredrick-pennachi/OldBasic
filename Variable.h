#pragma once

#include "ValueType.h"

#include <string>

class Variable
{
public:
	Variable();

	Variable(const std::string& name, ValueType::Enum valueType);

	std::string name;

	ValueType::Enum valueType;
};
