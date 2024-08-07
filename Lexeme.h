#pragma once

#include <string>
#include <map>

enum TokenName { UNSET, INTEGER, ID, OPERATOR, SEPARATOR, STRING };

static const std::map<TokenName, std::string> TokenNameMap = {
	{UNSET, "UNSET"},
	{INTEGER, "INTEGER"},
	{ID, "ID"},
	{OPERATOR, "OPERATOR"},
	{SEPARATOR, "SEPARATOR"},
	{STRING, "STRING"}
};

class Lexeme {
public:
	TokenName tokenName = UNSET;
	std::string value;
};
