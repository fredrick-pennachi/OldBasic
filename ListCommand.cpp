#include "ListCommand.h"

#include <iostream>

using namespace std;

const string ListCommand::LIST_COMMAND_NAME = "LIST";

ListCommand::ListCommand(const vector<Lexeme>& lexemes) : Command(LIST_COMMAND_NAME, lexemes) {
}

int ListCommand::invoke(Runtime& runtime)
{
	map<int, unique_ptr<Command>>::const_iterator it;

	for (it = runtime.program.cbegin(); it != runtime.program.cend(); it++) {
		Command& command = *(*it).second;
		cout << command << endl;
	}

	return 0;
}
