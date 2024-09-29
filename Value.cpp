#include "Value.h"

Value::Value() : valueType(ValueType::NONE), intValue(0), strValue("")
{
}

Value::Value(int intValue) : valueType(ValueType::INTEGER), intValue(intValue), strValue("")
{
}

Value::Value(std::string strValue) : valueType(ValueType::STRING), intValue(0), strValue(strValue)
{
}

ValueType::Enum Value::getType() const
{
	return valueType;
}

bool Value::evalBool() const
{
	if (getType() == ValueType::INTEGER) {
		return intValue != 0;
	}
	else if (getType() == ValueType::STRING) {
		return strValue.length() > 0;
	}
	else {
		return false;
	}
}

Value operator*(const Value& lhs, const Value& rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.intValue * rhs.intValue);
	}
	else {
		throw InvalidOperatorExeption("operator* is not valid for these values!");
	}
}

Value operator/(const Value& lhs, const Value& rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.intValue / rhs.intValue);
	}
	else {
		throw InvalidOperatorExeption("operator/ is not valid for these values!");
	}
}

Value operator+(const Value& lhs, const Value& rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.intValue + rhs.intValue);
	}
	else {
		// operator+ is also allowed for strings.
		return Value(lhs.strValue + rhs.strValue);
	}
}

Value operator-(const Value& lhs, const Value& rhs)
{
	Value retVal;

	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.intValue - rhs.intValue);
	}
	else {
		throw InvalidOperatorExeption("operator- is not valid for these values!");
	}

	return retVal;
}

bool operator<(const Value& lhs, const Value& rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return lhs.intValue < rhs.intValue;
	}
	else {
		throw InvalidOperatorExeption("operator<= is not valid for these values!");
	}
}

bool operator<=(const Value& lhs, const Value& rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return lhs.intValue <= rhs.intValue;
	}
	else {
		throw InvalidOperatorExeption("operator<= is not valid for these values!");
	}
}

std::ostream& operator<<(std::ostream& stream, const Value& value) {
	if (value.getType() == ValueType::INTEGER) {
		stream << value.intValue;
	}
	else if (value.getType() == ValueType::STRING) {
		stream << value.strValue;
	}
	else {
		throw InvalidOperatorExeption("operator<< is not implemented for this type!");
	}

	return stream;
}

InvalidOperatorExeption::InvalidOperatorExeption(std::string what) : runtime_error(what)
{
}
