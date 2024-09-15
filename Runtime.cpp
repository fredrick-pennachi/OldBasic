#include "Runtime.h"


Runtime runtime;
std::map<int, std::unique_ptr<Command>> Runtime::program;

Runtime::Runtime()
{
	settings["debug"] = Value(0);
	settings["run_tests"] = Value(1);
}

int Runtime::run()
{
	nextLineIter = program.cbegin();

	while (nextLineIter != program.cend()) {
		int lineNumber = (*nextLineIter).first;

		Command& command = *(*nextLineIter).second;

		// Increment before invoking because invoking the command
		// may change the nextLine (e.g. loops).

		nextLineIter++;

		command.invoke();
	}

    return 0;
}

int Runtime::setNextLine(int nextLine)
{
	nextLineIter = program.find(nextLine);

	return 0;
}

void Runtime::setVariable(const std::string& name, const Value& variable)
{
	variables[name] = variable;
}

bool Runtime::hasVariable(const std::string& name)
{
	return variables.count(name);
}

Value Runtime::getVariable(const std::string& name)
{
	return variables.at(name);
}

void Runtime::setArray(const std::string& name, int size)
{
	arrays[name] = Array(size);
}

bool Runtime::hasArray(const std::string& name)
{
	return arrays.count(name);
}

void Runtime::setArrayValue(const std::string& name, int subscript, const Value& value)
{
	arrays.at(name).putValue(subscript, value);
}

Value Runtime::getArrayValue(const std::string& name, int subscript)
{
	return arrays.at(name).getValue(subscript);
}

Value Runtime::getSetting(const std::string& setting)
{
	return settings.at(setting);
}

void Runtime::clear()
{
	program.clear();

	nextLineIter = program.cbegin();

	variables.clear();
}

Runtime::~Runtime()
{
}

