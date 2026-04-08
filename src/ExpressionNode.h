/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Runtime.h"
#include "Value.h"

class ExpressionNode
{
public:
	enum NodeType { NULL_NODE, OPERATOR_NODE, VALUE_NODE,
		VARIABLE_NODE, ARRAY_NODE, FUNCTION_NODE };

	ExpressionNode(const Lexeme& lexeme, NodeType nodeType);
	
	virtual Value eval() = 0;

	virtual bool evalBool() = 0;

	virtual void print() = 0;

	Lexeme lexeme;

	NodeType nodeType;
};

class ExpressionException : public std::runtime_error {
public:
	ExpressionException(std::string what);
};
