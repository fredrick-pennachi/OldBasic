/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <stdexcept>
#include <string>
#include <vector>

#include "Lexeme.h"

class Tokenizer {
public:
	std::vector<Lexeme> tokenize(const std::string& line);
	static const unsigned char HIGH_BIT;
	bool isOperator(char c);
	bool isHighBit(char c);
};

class InvalidTokenExeption : public std::runtime_error {
public:
	InvalidTokenExeption(const std::string what);
};
