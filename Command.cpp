#include "Command.h"

#include <iostream>

Command::Command(const string& name, vector<Lexeme>& lexemes) : name(name), lexemes(lexemes)
{
}

Command::~Command()
{
	cout << "Destroyed " << name << u8" command 👻" << endl;
}

ostream& operator<<(ostream& stream, const Command& command) {
	if (command.lexemes.empty()) {
		return stream;
	}

	stream << command.lexemes[0].value;
	for (int i = 1; i < command.lexemes.size(); i++) {
		stream << " " << command.lexemes[i].value;
	}

	return stream;
}

InvalidSyntaxExeption::InvalidSyntaxExeption(string what) : runtime_error(what)
{
}
