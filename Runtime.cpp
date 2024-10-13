#include "Runtime.h"

#include <windows.h>

Runtime runtime;

Runtime::Runtime() : currentLineNumber(0), isReturn(false)
{
	SetConsoleOutputCP(CP_UTF8);    // Sets console output
	SetConsoleCP(CP_UTF8);          // Sets console input
	setlocale(LC_ALL, ".UTF8");     // Sets locale?

	settings["debug"] = Value(0);
	settings["run_tests"] = Value(1);
}

int Runtime::run()
{
	forLoops.clear();

	nextLineIter = program.cbegin();

	while (nextLineIter != program.cend()) {
		currentLineNumber = nextLineIter->first;

		Command& command = *(nextLineIter->second);

		// Increment before invoking because invoking the command
		// may change the nextLine (e.g. loops).

		nextLineIter++;

		command.invoke();
	}

    return OK;
}

int Runtime::stop()
{
	nextLineIter = program.cend();

	return OK;
}

int Runtime::setNextLine(int nextLine)
{
	nextLineIter = program.find(nextLine);

	return OK;
}

void Runtime::setVariable(const Variable& variable)
{
	variables[variable.name] = variable;
}

bool Runtime::hasVariable(const std::string& name)
{
	return variables.count(name);
}

Variable& Runtime::getVariable(const std::string& name)
{
	return variables.at(name);
}

void Runtime::setArray(const std::string& name, int size)
{
	arrays[name] = Array(size);
}

bool Runtime::hasArray(const std::string& name)
{
	return arrays.count(name);
}

void Runtime::setArrayValue(const std::string& name, int subscript, const Value& value)
{
	arrays.at(name).putValue(subscript, value);
}

Value Runtime::getArrayValue(const std::string& name, int subscript)
{
	return arrays.at(name).getValue(subscript);
}

Value Runtime::getSetting(const std::string& setting)
{
	return settings.at(setting);
}

void Runtime::setForLoop(const Variable& variable)
{
	variables[variable.name] = variable;

	forLoops[variable.name] = currentLineNumber;
}

void Runtime::setGosub(int nextLine)
{
	// Save the current line on the gosubs stack
	// so it can be returned to.

	gosubs.push(currentLineNumber);
	setNextLine(nextLine);
}

void Runtime::returnGosub()
{
	// Set the next line to the line at the top of the gosubs
	// stack then pop it off, set the return flag so that gosub
	// doesn't jump again.


	if (!gosubs.empty()) {
		nextLineIter = program.find(gosubs.top());
		isReturn = true;
		gosubs.pop();
	}
}

void Runtime::clearProgram()
{
	program.clear();
	nextLineIter = program.cbegin();
	currentLineNumber = 0;
	variables.clear();
	arrays.clear();
	forLoops.clear();
}

void Runtime::clearScreen()
{
	// From https://learn.microsoft.com/en-us/windows/console/clearing-the-screen

	HANDLE hStdOut;

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	// Fetch existing console mode so we correctly add a flag and not turn off others
	DWORD mode = 0;
	if (!GetConsoleMode(hStdOut, &mode))
	{
		// Something weird has happened!
		std::cout << "GetConsoleMode failed!" << std::endl
			<< ::GetLastError() << std::endl;
		return;
	}

	// Hold original mode to restore on exit to be cooperative with other command-line apps.
	const DWORD originalMode = mode;
	mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	// Try to set the mode.
	if (!SetConsoleMode(hStdOut, mode))
	{
		std::cout << "SetConsoleMode failed!" << std::endl
			<< ::GetLastError() << std::endl;
		return;

	}

	// Write the sequence for clearing the display.
	DWORD written = 0;
	PCWSTR sequence = L"\x1b[2J";
	if (!WriteConsoleW(hStdOut, sequence, (DWORD)wcslen(sequence), &written, NULL))
	{
		// If we fail, try to restore the mode on the way out.
		SetConsoleMode(hStdOut, originalMode);
		std::cout << "WriteConsoleW failed!" << std::endl
			<< ::GetLastError() << std::endl;
		return;

	}

	// To also clear the scroll back, emit L"\x1b[3J" as well.
	// 2J only clears the visible window and 3J only clears the scroll back.

	// Restore the mode on the way out to be nice to other command-line applications.
	SetConsoleMode(hStdOut, originalMode);

	// Move the cursor to the top left corner too.
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hStdOut, csbi.dwCursorPosition);
}

void Runtime::sleep(int millis)
{
	Sleep(millis);
}

Runtime::~Runtime()
{
}

