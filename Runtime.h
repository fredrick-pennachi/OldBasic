#pragma once

#include "Command.h"
#include "Variable.h"

#include <list>
#include <map>
#include <memory>

class Command;

class Runtime
{
public:
	Runtime(const std::map<int, std::unique_ptr<Command>>& program);

	int run();

	int setNextLine(int nextLine);

	void setVariable(const std::string name, const std::string value);

	Variable getVariable(const std::string name);

	const std::map<int, std::unique_ptr<Command>>& program;

	std::map<int, std::unique_ptr<Command>>::const_iterator nextLineIter;

	std::map<std::string, Variable> variables;
};
