#pragma once

#include "Array.h"
#include "Command.h"
#include "Value.h"
#include "Variable.h"

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <stack>

class Command;

class Runtime
{
public:
	Runtime();

	int run();

	int stop();

	int setNextLine(int nextLine);

	void setVariable(const Variable& variable);

	bool hasVariable(const std::string& name);

	Variable& getVariable(const std::string& name);

	void setArray(const std::string& name, int size);

	bool hasArray(const std::string& name);

	void setArrayValue(const std::string& name, int subscript, const Value& value);

	Value getArrayValue(const std::string& name, int subscript);

	Value getSetting(const std::string& setting);

	std::string getInkeyInput();

	void setForLoop(const Variable& variable);

	void setGosub(int nextLine);

	void returnGosub();

	void clearProgram();

	void clearScreen();

	void sleep(int millis);

	std::map<int, std::unique_ptr<Command>> program;

	std::map<int, std::unique_ptr<Command>>::const_iterator nextLineIter;

	int currentLineNumber;

	std::map<std::string, Variable> variables;

	std::map<std::string, Array> arrays;

	std::map<std::string, int> forLoops;

	std::stack<int> gosubs;

	std::map<std::string, Value> settings;

	bool isReturn;

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
