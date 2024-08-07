#include "Value.h"

Value::Value() : type(NONE), intValue(0), strValue("")
{
}

Value::Value(int intValue) : type(INTEGER), intValue(intValue), strValue("")
{
}

Value::Value(std::string strValue) : type(STRING), intValue(0), strValue(strValue)
{
}

Value operator*(const Value& lhs, const Value& rhs)
{
	Value retVal;

	if (lhs.type == Value::INTEGER && rhs.type == Value::INTEGER) {
		retVal.type = Value::INTEGER;
		retVal.intValue = lhs.intValue * rhs.intValue;
	}
	else {
		throw InvalidOperatorExeption("operator* is not valid for these values!");
	}

	return retVal;
}

Value operator/(const Value& lhs, const Value& rhs)
{
	Value retVal;

	if (lhs.type == Value::INTEGER && rhs.type == Value::INTEGER) {
		retVal.type = Value::INTEGER;
		retVal.intValue = lhs.intValue / rhs.intValue;
	}
	else {
		throw InvalidOperatorExeption("operator/ is not valid for these values!");
	}

	return retVal;
}

Value operator+(const Value& lhs, const Value& rhs)
{
	Value retVal;

	if (lhs.type == Value::INTEGER && rhs.type == Value::INTEGER) {
		retVal.type = Value::INTEGER;
		retVal.intValue = lhs.intValue + rhs.intValue;
	}
	else {
		retVal.type = Value::STRING;
		retVal.strValue = lhs.strValue + rhs.strValue;
	}

	return retVal;
}

Value operator-(const Value& lhs, const Value& rhs)
{
	Value retVal;

	if (lhs.type == Value::INTEGER && rhs.type == Value::INTEGER) {
		retVal.type = Value::INTEGER;
		retVal.intValue = lhs.intValue - rhs.intValue;
	}
	else {
		throw InvalidOperatorExeption("operator- is not valid for these values!");
	}

	return retVal;
}

std::ostream& operator<<(std::ostream& stream, const Value& value) {
	if (value.type == Value::INTEGER) {
		stream << value.intValue;
	}
	else {
		stream << value.strValue;
	}

	return stream;
}

InvalidOperatorExeption::InvalidOperatorExeption(std::string what) : runtime_error(what)
{
}
