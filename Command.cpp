#include "Command.h"

#include <iostream>

Command::Command(const std::string& name, const std::vector<Lexeme>& lexemes) : name(name), lexemes(lexemes)
{
}

Command::~Command()
{
	runtime << "Destroyed " << name << u8" command 👻" << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const Command& command) {
	if (command.lexemes.empty()) {
		return stream;
	}

	stream << command.lexemes[0].value;
	for (int i = 1; i < command.lexemes.size(); i++) {
		stream << " " << command.lexemes[i].value;
	}

	return stream;
}

InvalidSyntaxExeption::InvalidSyntaxExeption(std::string what) : runtime_error(what)
{
}
