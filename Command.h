#pragma once

#include "Lexeme.h"
#include "Runtime.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

class Runtime;

using namespace std;

class Command {
public:
	Command(const string& name, const vector<Lexeme>& lexemes);

	virtual int invoke(Runtime& runtime) = 0;

	virtual ~Command();

	string name;

	vector<Lexeme> lexemes;

private:
	Command();
};

ostream& operator<<(ostream& stream, const Command& command);

class InvalidSyntaxExeption : public runtime_error {
public:
	InvalidSyntaxExeption(string what);
};
