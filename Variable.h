#pragma once

#include <string>

using namespace std;

class Variable
{
public:
	Variable(const string& name, const string& value);

	string name;
	string value;
};
