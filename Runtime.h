#pragma once

#include "Command.h"
#include "Variable.h"

#include <list>
#include <map>
#include <memory>

using namespace std;

class Command;

class Runtime
{
public:
	Runtime(const map<int, unique_ptr<Command>>& program);

	int run();

	int setNextLine(int nextLine);

	void setVariable(const string name, const string value);

	Variable getVariable(const string name);

	const map<int, unique_ptr<Command>>& program;

	map<int, unique_ptr<Command>>::const_iterator nextLineIter;

	map<string, Variable> variables;
};
