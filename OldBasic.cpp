#include "ForCommand.h"
#include "Lexeme.h"
#include "Parser.h"
#include "Runtime.h"
#include "Test.h"
#include "Tokenizer.h"

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

	if (runtime.getSetting("run_tests").evalBool()) {
		runTests(tokenizer, parser);
	}
	
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
		Command* commandPtr = command.get();

		if (commandPtr->name == ForCommand::FOR_COMMAND_NAME)
		{
			// Write the line to line number zero if
			// it's a single line loop, then remove
			// it so that it isn't present for future
			// execution.
			runtime.program[0] = move(command);
			commandPtr->invoke();
			runtime.program.erase(0);
		}
		else {
			commandPtr->invoke();
		}
	}
}

void runTests(Tokenizer& tokenizer, Parser& parser)
{
	std::vector<Test> tests;

	tests.push_back(Test("multiply precedence", "LET A = 1 + 2 * 3",
		[]() {
			return runtime.getVariable("A").value.intValue == 7;
		}));

	tests.push_back(Test("colon separation   ", "LET B = 4 : LET C = 5 : LET D = 6",
		[]() {
			return runtime.getVariable("B").value.intValue == 4 &&
				runtime.getVariable("C").value.intValue == 5 &&
				runtime.getVariable("D").value.intValue == 6;
		}));

	tests.push_back(Test("negative numbers   ", "LET E = -5 + 2 : LET F = 3 - -7",
		[]() {
			return runtime.getVariable("E").value.intValue == -3 &&
				runtime.getVariable("F").value.intValue == 10;
		}));

	tests.push_back(Test("for loop           ",
		"LET G = 0 : FOR I = 1 TO 10 : LET G = G + 1 : NEXT I",
		[]() {
			return runtime.getVariable("G").value.intValue == 10;
		}));

	tests.push_back(Test("nested for loop    ",
		"LET H = 0 : FOR I = 1 TO 9 : FOR J = 1 TO 9 : LET H = H + 1 : NEXT J : NEXT I",
		[]() {
			return runtime.getVariable("H").value.intValue == 81;
		}));

	for (Test test : tests) {
		evalLine(tokenizer, parser, test.testStatement);
		bool result = test.assert();
		if (result) {
			runtime << u8"🍇 OK   ";
		}
		else {
			runtime << u8"🍄 FAIL ";
		}
		runtime << test.testName << u8" ⌨️ " << test.testStatement << std::endl;
	}

	runtime.clear();

	runtime << std::endl;

	evalLine(tokenizer, parser, "dim f(5)");
	evalLine(tokenizer, parser, "let f(1) = 5 : let f(2) = 7");
	evalLine(tokenizer, parser, "dim");

	runtime << std::endl;

}
