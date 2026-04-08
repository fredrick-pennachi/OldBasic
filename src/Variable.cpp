// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Variable.h"

Variable::Variable()
{
}

Variable::Variable(const std::string& name, Value value) : name(name), value(value)
{
}

std::ostream& operator<<(std::ostream& stream, const Variable& var) {
	stream << var.name << ": " << var.value;
	return stream;
}