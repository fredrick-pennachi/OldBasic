#pragma once

#include <string>

using namespace std;

class Variable
{
public:
	Variable(string name, string value);

	string name;
	string value;
};
