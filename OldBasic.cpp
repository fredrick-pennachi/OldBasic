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

using namespace std;

int main()
{
	SetConsoleOutputCP(CP_UTF8);    // Sets console output
	SetConsoleCP(CP_UTF8);          // Sets console input
	setlocale(LC_ALL, ".UTF8");     // Sets locale?

	const string PROMPT = u8"> ";

	map<int, unique_ptr<Command>> program;

	Tokenizer tokenizer;
	Parser parser;
	Runtime runtime(program);

	string line;

	cout << u8"OLD BASIC 🐻 🎨 🥗 🍨 🍒 🤖" << endl;
	cout << endl;
	//cout << u8"🦚 🐻 🍔 🌭 🥗 🥪" << endl;

	while (true) {
		cout << PROMPT;

		// Get a line of input
		getline(cin, line);

		if (line == "q" || line == "Q" || line == "exit") {
			break;
		}

		try {
			// Tokenize line
			vector<Lexeme> lexemes = tokenizer.tokenize(line);

			// Some early debugging logic, should probably remove.
			/*for (vector<Lexeme>::iterator i = lexemes.begin(); i != lexemes.end(); i++) {
				Lexeme& lexeme = *i;
				cout << TokenNameMap.at(lexeme.tokenName) << " " << lexeme.value << endl;
			}*/

			if (lexemes.size() == 0) {
				continue;
			}

			// Turn tokens into command
			unique_ptr<Command> command = parser.parse(lexemes);
			// If first token is a line number then add to program
			// otherwise invoke immediately.
			if (lexemes[0].tokenName == INTEGER) {
				int lineNumber = stoi(lexemes[0].value);
				program[lineNumber] = move(command);
				cout << u8"🥗 OK" << endl;
			}
			else {
				// No line number, invoke immediately.
				(*command).invoke(runtime);
			}
		}
		catch (exception& e) {
			cout << u8"🐞 ERROR: " << e.what() << endl;
		}		
	}

	cout << u8"Goodbye! 👋" << endl;

	return 0;
}
