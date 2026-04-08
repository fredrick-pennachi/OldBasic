/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "../Runtime.h"

Runtime runtime;

Runtime::Runtime() : currentLineNumber(0), isReturn(false)
{
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

std::string Runtime::getInkeyInput()
{
	// TODO: Come back and fix this!

	// if (_kbhit()) {
	// 	return std::string({ (char) _getch() });
	// }
	// else {
	// 	return std::string("");
	// }

	return std::string("");
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
	// TODO: Find the Linux version of this!
	
}

void Runtime::sleep(int millis)
{
	// TODO: Find the Linux version of this!

	// Sleep(millis);
}

Runtime::~Runtime()
{
}

