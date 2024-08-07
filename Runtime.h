#pragma once

#include "Command.h"
#include "Variable.h"

#include <iostream>
#include <list>
#include <map>
#include <memory>

class Command;

class Runtime
{
public:
	Runtime();

	int run();

	int setNextLine(int nextLine);

	void setVariable(const std::string name, const std::string value);

	Variable getVariable(const std::string name);

	static std::map<int, std::unique_ptr<Command>> program;

	std::map<int, std::unique_ptr<Command>>::const_iterator nextLineIter;

	std::map<std::string, Variable> variables;

	template<typename T>
	Runtime& operator<<(const T& object)
	{
		std::cout << object;
		return *this;
	}

	Runtime& operator<<(std::ostream& (*pManip)(std::ostream&))
	{
		std::cout << (*pManip);
		return *this;
	}

	~Runtime();
};

extern Runtime runtime;
