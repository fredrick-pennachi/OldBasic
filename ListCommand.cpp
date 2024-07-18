#include "ListCommand.h"

#include <iostream>

using namespace std;

const string ListCommand::LIST_COMMAND_NAME = "LIST";

ListCommand::ListCommand(vector<Lexeme>& lexemes) : Command(LIST_COMMAND_NAME, lexemes) {
}

int ListCommand::invoke(Runtime& runtime)
{
	map<int, unique_ptr<Command>>::iterator it;

	for (it = runtime.program.begin(); it != runtime.program.end(); it++) {
		Command& command = *(*it).second;
		cout << command << endl;
	}

	return 0;
}
