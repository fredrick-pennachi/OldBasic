#pragma once

#include <string>
#include <map>

using namespace std;

enum TokenName { UNSET, INTEGER, ID, OPERATOR, SEPARATOR, STRING };

static const map<TokenName, string> TokenNameMap = {
	{UNSET, "UNSET"},
	{INTEGER, "DIGIT"},
	{ID, "ID"},
	{OPERATOR, "OPERATOR"},
	{SEPARATOR, "SEPARATOR"},
	{STRING, "STRING"}
};

class Lexeme {
public:
	TokenName tokenName = UNSET;
	string value;
};
