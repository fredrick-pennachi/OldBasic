#pragma once

#include "Lexeme.h"
#include "Runtime.h"

#include <exception>
#include <iostream>
#include <string>
#include <vector>

class Runtime;

class Command {
public:
	Command(const std::string& name, const std::vector<Lexeme>& lexemes);

	virtual int invoke() = 0;

	virtual ~Command();

	std::string name;

	std::vector<Lexeme> lexemes;

private:
	Command();
};

std::ostream& operator<<(std::ostream& stream, const Command& command);

class InvalidSyntaxException : public std::runtime_error {
public:
	InvalidSyntaxException(std::string what);
};

class RuntimeException : public std::runtime_error {
public:
	RuntimeException(std::string what);
};
