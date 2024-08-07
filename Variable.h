#pragma once

#include <string>

class Variable
{
public:
	Variable(const std::string& name, const std::string& value);

	std::string name;
	std::string value;
};
