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

	std::map<int, std::unique_ptr<Command>> program;

	Tokenizer tokenizer;
	Parser parser;
	Runtime runtime(program);

	std::string line;

	std::cout << u8"OLD BASIC 🐻 🎨 🥗 🍨 🍒 🤖" << std::endl;
	std::cout << std::endl;
	//cout << u8"🦚 🐻 🍔 🌭 🥗 🥪" << endl;

	while (true) {
		std::cout << PROMPT;

		// Get a line of input
		getline(std::cin, line);

		if (line == "q" || line == "Q" || line == "exit") {
			break;
		}

		try {
			// Tokenize line
			std::vector<Lexeme> lexemes = tokenizer.tokenize(line);

			// Some early debugging logic, should probably remove.
			/*for (std::vector<Lexeme>::iterator i = lexemes.begin(); i != lexemes.end(); i++) {
				Lexeme& lexeme = *i;
				cout << TokenNameMap.at(lexeme.tokenName) << " " << lexeme.value << endl;
			}*/

			if (lexemes.size() == 0) {
				continue;
			}

			// Turn tokens into command
			std::unique_ptr<Command> command = parser.parse(lexemes);
			// If first token is a line number then add to program
			// otherwise invoke immediately.
			if (lexemes[0].tokenName == INTEGER) {
				int lineNumber = stoi(lexemes[0].value);
				program[lineNumber] = move(command);
				std::cout << u8"🥗 OK" << std::endl;
			}
			else {
				// No line number, invoke immediately.
				(*command).invoke(runtime);
			}
		}
		catch (std::exception& e) {
			std::cout << u8"🐞 ERROR: " << e.what() << std::endl;
		}		
	}

	std::cout << u8"Goodbye! 👋" << std::endl;

	return 0;
}
