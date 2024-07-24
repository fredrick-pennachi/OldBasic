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
	Runtime(map<int, unique_ptr<Command>>& program);

	int run();

	int setNextLine(int nextLine);

	void setVariable(string name, string value);
	Variable getVariable(string name);

	map<int, unique_ptr<Command>>& program;

	map<int, unique_ptr<Command>>::iterator nextLineIter;

	map<string, Variable> variables;
};
