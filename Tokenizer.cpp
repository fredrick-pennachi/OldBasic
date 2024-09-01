#include "Tokenizer.h"

#include <iostream>
#include <cctype>

const char Tokenizer::HIGH_BIT = 128;

std::vector<Lexeme> Tokenizer::tokenize(const std::string& line) {

	std::vector<Lexeme> lexemes;

	for (std::string::const_iterator i = line.begin(); i != line.end(); /* iterator is advanced inside loop */) {

		// Whitespace is between lexemes, move to a non-whitespace char.
		if (i != line.end() && isspace(*i)) {
			i++;
			continue;
		}

		Lexeme lexeme;

		// Identify the type of token by the starting character then parse
		// additional characters to create the Lexeme.

		// Number
		if (isdigit(*i)) {
			lexeme.tokenName = INTEGER;
			lexeme.value += *i;
			i++;
			while (i != line.end() && isdigit(*i)) {
				lexeme.value += *i;
				i++;
			}
			lexemes.push_back(lexeme);
			continue;
		}

		// Negative number
		if (*i == '-' && (i + 1) != line.end() && isdigit(*(i + 1))) {
			lexeme.tokenName = INTEGER;
			lexeme.value += *i;
			i++;
			while (i != line.end() && isdigit(*i)) {
				lexeme.value += *i;
				i++;
			}
			lexemes.push_back(lexeme);
				continue;
		}

		// Id, convert to uppercase
		if (isalpha(*i) || isHighBit(*i)) {
			lexeme.tokenName = ID;
			lexeme.value += toupper(*i);
			i++;
			while (i != line.end() && !isspace(*i) && !ispunct(*i)) {
				lexeme.value += toupper(*i);
				i++;
			}
			lexemes.push_back(lexeme);
			continue;
		}

		// Operator
		if (isOperator(*i)) {
			lexeme.tokenName = OPERATOR;
			lexeme.value += *i;
			i++;
			while (i != line.end() && isOperator(*i)) {
				lexeme.value += *i;
				i++;
			}
			lexemes.push_back(lexeme);
			continue;
		}

		// Separator
		if (*i == ',' || *i == ';' || *i == ':') {
			lexeme.tokenName = SEPARATOR;
			lexeme.value += *i;
			i++;
			lexemes.push_back(lexeme);
			continue;
		}

		// String
		if (*i == '"') {
			lexeme.tokenName = STRING;

			// Save the first quotation mark.
			lexeme.value += *i;
			i++;
			while (i != line.end()  && *i != '"') {
				if (*i == '\\') {
					// The next character is escaped so should be added to the value.
					i++;
					lexeme.value += *i;
				}
				else {
					lexeme.value += *i;
				}
				i++;
			}

			if (i == line.end() || *i != '"') {
				throw InvalidTokenExeption("STRING isn't terminated with quotation mark!");
			}
			else {
				// Save the closing quotation mark too.
				lexeme.value += *i;
				i++;
				lexemes.push_back(lexeme);
				continue;
			}
		}

		// Shouldn't reach this point but in case we do we don't want to be stuck in an unbound loop.
		i++;
	}

	return lexemes;
}

bool Tokenizer::isOperator(char c) {
	switch (c) {
		case '(':
		case ')':
		case '^':
		case '*':
		case '/':
		case '+':
		case '-':
		case '<':
		case '>':
		case '=':
			return true;
		default:
			return false;
	}
}

bool Tokenizer::isHighBit(char c) {
	return c & HIGH_BIT;
}

InvalidTokenExeption::InvalidTokenExeption(const std::string what) : runtime_error(what)
{
}
