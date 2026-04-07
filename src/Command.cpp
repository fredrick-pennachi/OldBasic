#include "Command.h"

Command::Command(const std::string& name, const std::vector<Lexeme>& lexemes) : name(name), lexemes(lexemes)
{
}

Command::~Command()
{
	// Commenting this out for now because it's causing an
	// exception at program exit, presumably accessing
	// a destroyed map or something.
	
	//if (runtime.getSetting("debug").evalBool()) {
	//	runtime << "Destroyed " << name << u8" command 👻" << std::endl;
	//}
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

InvalidSyntaxException::InvalidSyntaxException(std::string what) : runtime_error(what)
{
}

RuntimeException::RuntimeException(std::string what) : runtime_error(what)
{
}

