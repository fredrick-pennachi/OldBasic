#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "Lexeme.h"

using namespace std;

class Tokenizer {
public:
	vector<Lexeme> tokenize(const string& line);
	static const char HIGH_BIT;
	bool isoperator(char c);
	bool ishighbit(char c);
};

class InvalidTokenExeption : public runtime_error {
public:
	InvalidTokenExeption(string what);
};
