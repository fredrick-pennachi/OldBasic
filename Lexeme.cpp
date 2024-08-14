#include "Lexeme.h"

bool operator==(const Lexeme& l1, const Lexeme& l2) {

	return (l1.tokenName == l2.tokenName) && (l1.value == l2.value);
}
