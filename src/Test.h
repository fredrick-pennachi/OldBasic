/*
 * SPDX-FileCopyrightText: 2026 Fredrick Pennachi
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include <string>

class Test
{
public:
	Test(std::string testName, std::string testStatement, bool(*assert)());

	std::string testName;

	std::string testStatement;

	bool(*assert)();
};

