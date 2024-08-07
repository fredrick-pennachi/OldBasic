#include "Tokenizer.h"
#include "Lexeme.h"
#include "Parser.h"
#include "Runtime.h"

#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>
#include <map>
#include <memory>

int main()
{
	SetConsoleOutputCP(CP_UTF8);    // Sets console output
	SetConsoleCP(CP_UTF8);          // Sets console input
	setlocale(LC_ALL, ".UTF8");     // Sets locale?

	const std::string PROMPT = u8"> ";

	Tokenizer tokenizer;
	Parser parser;

	std::string line;

	runtime << u8"OLD BASIC 🐻 🎨 🥗 🍨 🍒 🤖 🦚 🍔 🌭 🥪" << std::endl;
	runtime << std::endl;

	while (true) {
		runtime << PROMPT;

		// Get a line of input
		getline(std::cin, line);

		if (line == "q" || line == "Q" || line == "exit") {
			break;
		}

		try {
			// Tokenize line
			std::vector<Lexeme> lexemes = tokenizer.tokenize(line);

			if (lexemes.size() == 0) {
				continue;
			}

			// Turn tokens into command
			std::unique_ptr<Command> command = parser.parse(lexemes);
			// If first token is a line number then add to program
			// otherwise invoke immediately.
			if (lexemes[0].tokenName == INTEGER) {
				int lineNumber = stoi(lexemes[0].value);
				runtime.program[lineNumber] = move(command);
				runtime << u8"🥗 OK" << std::endl;
			}
			else {
				// No line number, invoke immediately.
				(*command).invoke();
			}
		}
		catch (std::exception& e) {
			runtime << u8"🐞 ERROR: " << e.what() << std::endl;
		}		
	}

	runtime << u8"Goodbye! 👋" << std::endl;

	return 0;
}
