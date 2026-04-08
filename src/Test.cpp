// SPDX-FileCopyrightText: 2026 Fredrick Pennachi
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "Test.h"

Test::Test(std::string testName, std::string testStatement, bool(*assert)())
	: testName(testName), testStatement(testStatement), assert(assert)
{
}
