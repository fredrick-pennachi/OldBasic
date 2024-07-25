#include "Runtime.h"

Runtime::Runtime(const map<int, unique_ptr<Command>>& program) : program(program) {
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

		command.invoke(*this);
	}

    return 0;
}

int Runtime::setNextLine(int nextLine)
{
	nextLineIter = program.find(nextLine);

	return 0;
}

void Runtime::setVariable(string name, string value)
{
	variables.emplace(name, Variable(name, value));
}

Variable Runtime::getVariable(string name)
{
	return variables.at(name);
}

