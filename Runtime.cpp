#include "Runtime.h"


Runtime runtime;
std::map<int, std::unique_ptr<Command>> Runtime::program;

Runtime::Runtime()
{
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

void Runtime::setVariable(std::string name, std::string value)
{
	variables.emplace(name, Variable(name, value));
}

Variable Runtime::getVariable(std::string name)
{
	return variables.at(name);
}

Runtime::~Runtime()
{
}

