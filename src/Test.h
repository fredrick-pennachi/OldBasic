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

