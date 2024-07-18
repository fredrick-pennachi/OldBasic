#include "Runtime.h"

Runtime::Runtime(map<int, unique_ptr<Command>>& program) : program(program) {
}

int Runtime::run()
{
	nextLineIter = program.begin();

	while (nextLineIter != program.end()) {
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

