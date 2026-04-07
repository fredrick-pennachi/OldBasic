#include "Test.h"

Test::Test(std::string testName, std::string testStatement, bool(*assert)())
	: testName(testName), testStatement(testStatement), assert(assert)
{
}
