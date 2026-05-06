// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "CLI11.hpp"

#include "ForCommand.h"
#include "Lexeme.h"
#include "Parser.h"
#include "ReadEval.h"
#include "RunCommand.h"
#include "Runtime.h"
#include "Test.h"
#include "Tokenizer.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <map>
#include <memory>

void runTests();

int main(int argc, char** argv)
{
	// Command line options.

	CLI::App app{ "OldBasic BASIC Interpreter" };
	argv = app.ensure_utf8(argv);

	std::string filename = "";
	app.add_option("filename", filename, "Filename for a BASIC program");

	bool showCommands = false;
	app.add_flag("-c, --commands", showCommands, "Prints a command listing");

	CLI11_PARSE(app, argc, argv);


	if (showCommands) {
		std::cout << "show the commands!\n";
	}

	// If a filename is supplied then load the program from it
	// and run it then exit. Otherwise start the REPL.

	if (filename != "") {
		
		readEval.readFile(filename);

		// Run the program.
		try {
			runtime.run();
		}
		catch (std::exception& e) {
			runtime << u8"🐞 ERROR (line "
				<< runtime.currentLineNumber << "): "
				<< e.what() << std::endl;
		}
	}
	else {
		if (runtime.getSetting("run_tests").evalBool()) {
			runTests();
		}

		runtime << u8"OLD BASIC 🐻 🎨 🥗 🍨 🍒 🤖 🦚 🍔 🌭 🥪" << std::endl;
		runtime << std::endl;

		const std::string PROMPT = u8"> ";
		std::string line;

		while (true) {
			runtime << PROMPT;

			// Get a line of input
			getline(std::cin, line);

			if (line == "q" || line == "Q" || line == "quit" || line == "exit") {
				break;
			}

			try {
				readEval.evalLine(line);
			}
			catch (std::exception& e) {
				std::string uppercaseLine;
				uppercaseLine.resize(line.size());
				std::transform(line.begin(), line.end(), uppercaseLine.begin(), ::toupper);
				if (uppercaseLine == "RUN") {
					runtime << u8"🐞 ERROR (line "
						<< runtime.currentLineNumber << "): "
						<< e.what() << std::endl;
				}
				else {
					runtime << u8"🐞 ERROR: " << e.what() << std::endl;
				}
			}
		}

		runtime << u8"Goodbye! 👋" << std::endl;
	}

	return OK;
}

void runTests()
{
	std::vector<Test> tests;

	tests.push_back(Test("multiply precedence", "LET A = 1 + 2 * 3",
		[]() {
			return runtime.getVariable("A").value.intValue == 7;
		}));

	tests.push_back(Test("order of div/mult  ", "LET Y = 12 / 2 * 3",
		[]() {
			return runtime.getVariable("Y").value.intValue == 18;
		}));

	tests.push_back(Test("string join        ", u8"LET A$ = \"🍷\" : LET B$ = \"🧀\" : LET C$ = A$;B$",
		[]() {
			return runtime.getVariable("A$").value.strValue == u8"🍷" &&
				runtime.getVariable("B$").value.strValue == u8"🧀" &&
			runtime.getVariable("C$").value.strValue == u8"🍷🧀";
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

	tests.push_back(Test("decimal numbers    ", "LET K = 0.5 : LET K_INT = 123 : LET L = K + K_INT",
		[]() {
			return runtime.getVariable("K").value.floatValue == 0.5f &&
				runtime.getVariable("K_INT").value.intValue == 123 &&
				runtime.getVariable("L").value.floatValue == 123.5f;
		}));

	tests.push_back(Test("array values       ", "DIM A(5) : LET A(1) = 5 : LET A(2) = 7",
		[]() {
			return runtime.getArrayValue("A", 1).intValue == 5 &&
				runtime.getArrayValue("A", 2).intValue == 7;
		}));

	for (Test test : tests) {
		readEval.evalLine(test.testStatement);
		bool result = test.assert();
		if (result) {
			runtime << u8"🍇 OK   ";
		}
		else {
			runtime << u8"🍄 FAIL ";
		}
		runtime << test.testName << u8" ⌨️ " << test.testStatement << std::endl;

		runtime.clearProgram();
	}

	runtime << std::endl;
}
