#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "Lexeme.h"

class Tokenizer {
public:
	std::vector<Lexeme> tokenize(const std::string& line);
	static const char HIGH_BIT;
	bool isOperator(char c);
	bool isHighBit(char c);
};

class InvalidTokenExeption : public std::runtime_error {
public:
	InvalidTokenExeption(const std::string what);
};
