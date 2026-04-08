/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Value.h"

#include <string>

class Variable
{
public:
	Variable();

	Variable(const std::string& name, Value value);

	std::string name;

	Value value;
};

std::ostream& operator<<(std::ostream& stream, const Variable& value);
