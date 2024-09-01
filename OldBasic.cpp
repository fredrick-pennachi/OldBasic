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

void evalLine(Tokenizer& tokenizer, Parser& parser, std::string line);
void runTests(Tokenizer& tokenizer, Parser& parser);

int main()
{
	SetConsoleOutputCP(CP_UTF8);    // Sets console output
	SetConsoleCP(CP_UTF8);          // Sets console input
	setlocale(LC_ALL, ".UTF8");     // Sets locale?
	
	Tokenizer tokenizer;
	Parser parser;

	runTests(tokenizer, parser);
	
	runtime << u8"OLD BASIC 🐻 🎨 🥗 🍨 🍒 🤖 🦚 🍔 🌭 🥪" << std::endl;
	runtime << std::endl;

	const std::string PROMPT = u8"> ";
	std::string line;

	while (true) {
		runtime << PROMPT;

		// Get a line of input
		getline(std::cin, line);

		if (line == "q" || line == "Q" || line == "exit") {
			break;
		}

		try {
			evalLine(tokenizer, parser, line);
		}
		catch (std::exception& e) {
			runtime << u8"🐞 ERROR: " << e.what() << std::endl;
		}
	}

	runtime << u8"Goodbye! 👋" << std::endl;

	return 0;
}

void evalLine(Tokenizer& tokenizer, Parser& parser, std::string line)
{
	// Tokenize line
	std::vector<Lexeme> lexemes = tokenizer.tokenize(line);

	if (lexemes.size() == 0) {
		return;
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

void runTests(Tokenizer& tokenizer, Parser& parser)
{
	std::string multiplyPrecedence = "LET A = 1 + 2 * 3";

	runtime << "multiplyPrecedence: " << multiplyPrecedence << std::endl;

	evalLine(tokenizer, parser, multiplyPrecedence);

	if (runtime.getVariable("A").intValue == 7) {
		runtime << u8"🍇 OK" << std::endl;
	}
	else {
		runtime << u8"🍄 FAILED" << std::endl;
	}

	evalLine(tokenizer, parser, "NEW");

	runtime << std::endl;
}
