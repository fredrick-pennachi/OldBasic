#include "Tokenizer.h"

#include <iostream>
#include <cctype>

const unsigned char Tokenizer::HIGH_BIT = 128;

std::vector<Lexeme> Tokenizer::tokenize(const std::string& line) {

	std::vector<Lexeme> lexemes;
	
	// Control whether '-' should be parsed as the sign part
	// of a negative number or a subtraction operator.
	bool canNegative = true;

	for (std::string::const_iterator i = line.begin(); i != line.end(); /* iterator is advanced inside loop */) {

		// Whitespace is between lexemes, move to a non-whitespace char.
		if (i != line.end() && isspace(*i)) {
			i++;
			continue;
		}

		Lexeme lexeme;

		// Identify the type of token by the starting character then parse
		// additional characters to create the Lexeme.

		// Comment
		if (*i == '\'') {
			// Either this line, or the remainder of this line is a comment.
			return lexemes;
		}

		// Number
		if (isdigit(*i)) {
			lexeme.value += *i;
			i++;
			bool decimal = false;
			while (i != line.end() && (isdigit(*i) || *i == '.')) {
				if (*i == '.') {
					if (!decimal) {
						decimal = true;
					} else {
						throw InvalidTokenExeption("Too many decimal points in DBL_FLOAT number!");
					}
				}
				lexeme.value += *i;
				i++;
			}
			if (decimal) {
				lexeme.tokenName = DBL_FLOAT;
			}
			else {
				lexeme.tokenName = INTEGER;
			}
			lexemes.push_back(lexeme);
			canNegative = false;
			continue;
		}

		// Negative number
		if (canNegative && *i == '-' && (i + 1) != line.end() && isdigit(*(i + 1))) {
			lexeme.value += *i;
			i++;
			bool decimal = false;
			while (i != line.end() && (isdigit(*i) || *i == '.')) {
				if (*i == '.') {
					if (!decimal) {
						decimal = true;
					}
					else {
						throw InvalidTokenExeption("Too many decimal points in DBL_FLOAT number!");
					}
				}
				lexeme.value += *i;
				i++;
			}
			if (decimal) {
				lexeme.tokenName = DBL_FLOAT;
			}
			else {
				lexeme.tokenName = INTEGER;
			}
			lexemes.push_back(lexeme);
			canNegative = false;
			continue;
		}

		// Id, convert to uppercase
		if (isalpha(*i) || isHighBit(*i)) {
			lexeme.tokenName = ID;
			lexeme.value += toupper(*i);
			i++;
			while (i != line.end() && !isspace(*i) && !isOperator(*i) &&
				(isalpha(*i) || *i == '_' || *i == '$' || isHighBit(*i))) {
				lexeme.value += toupper(*i);
				i++;
			}

			// Some ids are actually operators.
			if (lexeme.value == "AND" || lexeme.value == "OR") {
				lexeme.tokenName = OPERATOR;
			}

			lexemes.push_back(lexeme);
			canNegative = false;
			continue;
		}

		// Operator
		if (isOperator(*i)) {
			lexeme.tokenName = OPERATOR;
			lexeme.value += *i;
			char c = *i;
			i++;
			if (c == '<') {
				// Could be less than or equal to, or not equal to.
				if (i != line.end() && (*i == '>' || *i == '=')) {
					lexeme.value += *i;
					i++;
				}
			}
			else if (c == '>') {
				// Could be greater than or equal to.
				if (i != line.end() && *i == '=') {
					lexeme.value += *i;
					i++;
				}
			}
			
			lexemes.push_back(lexeme);
			canNegative = true;
			continue;
		}

		// Separator
		if (*i == ',' || *i == ':') {
			lexeme.tokenName = SEPARATOR;
			lexeme.value += *i;
			i++;
			lexemes.push_back(lexeme);
			canNegative = true;
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
				canNegative = false;
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
		case ';':
		case ',':
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
