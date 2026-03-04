#include "Value.h"

#include <cmath>
#include <sstream>

const double Value::FLOAT_EPSILON = 1e-9;

Value::Value() : valueType(ValueType::NONE), intValue(0), strValue(""), floatValue(0.0f)
{
}

Value::Value(int intValue) : valueType(ValueType::INTEGER), intValue(intValue), strValue(""), floatValue(0.0f)
{
}

Value::Value(std::string strValue) : valueType(ValueType::STRING), intValue(0), strValue(strValue), floatValue(0.0f)
{
}

Value::Value(double floatValue) : valueType(ValueType::DBL_FLOAT), intValue(0), strValue(""), floatValue(floatValue)
{
}

Value Value::concat(const Value& lhs, const Value& rhs)
{
	std::stringstream ss;
	ss << lhs << rhs;
	return Value(ss.str());
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
	else if (getType() == ValueType::DBL_FLOAT) {
		return fabs(floatValue) < FLOAT_EPSILON;
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
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.floatValue * (double) rhs.intValue);
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return Value((double) lhs.intValue * rhs.floatValue);
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return Value(lhs.floatValue * rhs.floatValue);
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
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.floatValue / (double) rhs.intValue);
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return Value((double) lhs.intValue / rhs.floatValue);
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return Value(lhs.floatValue / rhs.floatValue);
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
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.floatValue + (double) rhs.intValue);
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return Value((double) lhs.intValue + rhs.floatValue);
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return Value(lhs.floatValue + rhs.floatValue);
	}
	else {
		throw InvalidOperatorExeption("operator+ is not valid for these values!");
	}
}

Value operator-(const Value& lhs, const Value& rhs)
{
	Value retVal;

	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.intValue - rhs.intValue);
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return Value(lhs.floatValue - (double) rhs.intValue);
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return Value((double) lhs.intValue - rhs.floatValue);
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return Value(lhs.floatValue - rhs.floatValue);
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
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return lhs.floatValue < (double) rhs.intValue;
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return (double) lhs.intValue < rhs.floatValue;
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return lhs.floatValue < rhs.floatValue;
	}
	else if (lhs.getType() == ValueType::STRING && rhs.getType() == ValueType::STRING) {
		return lhs.strValue < rhs.strValue;
	}
	else {
		throw InvalidOperatorExeption("operator< is not valid for these values!");
	}
}

bool operator<=(const Value& lhs, const Value& rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return lhs.intValue <= rhs.intValue;
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return (lhs.floatValue < (double)rhs.intValue) ||
			(fabs(lhs.floatValue - (double)rhs.intValue) < Value::FLOAT_EPSILON);
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return ((double)lhs.intValue < rhs.floatValue) ||
			(fabs((double)lhs.intValue - rhs.floatValue) < Value::FLOAT_EPSILON);
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return (lhs.floatValue < rhs.floatValue) ||
			(fabs(lhs.floatValue - rhs.floatValue) < Value::FLOAT_EPSILON);
	}
	else if (lhs.getType() == ValueType::STRING && rhs.getType() == ValueType::STRING) {
		return lhs.strValue <= rhs.strValue;
	}
	else {
		throw InvalidOperatorExeption("operator<= is not valid for these values!");
	}
}

bool operator>(const Value& lhs, const Value& rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return lhs.intValue > rhs.intValue;
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return lhs.floatValue > (double)rhs.intValue;
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return (double)lhs.intValue > rhs.floatValue;
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return lhs.floatValue > rhs.floatValue;
	}
	else if (lhs.getType() == ValueType::STRING && rhs.getType() == ValueType::STRING) {
		return lhs.strValue > rhs.strValue;
	}
	else {
		throw InvalidOperatorExeption("operator> is not valid for these values!");
	}
}

bool operator>=(const Value & lhs, const Value & rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return lhs.intValue >= rhs.intValue;
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return (lhs.floatValue > (double)rhs.intValue) ||
			(fabs(lhs.floatValue - (double)rhs.intValue) < Value::FLOAT_EPSILON);
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return ((double)lhs.intValue > rhs.floatValue) ||
			(fabs((double)lhs.intValue - rhs.floatValue) < Value::FLOAT_EPSILON);
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return (lhs.floatValue > rhs.floatValue) ||
			(fabs(lhs.floatValue - rhs.floatValue) < Value::FLOAT_EPSILON);
	}
	else if (lhs.getType() == ValueType::STRING && rhs.getType() == ValueType::STRING) {
		return lhs.strValue >= rhs.strValue;
	}
	else {
		throw InvalidOperatorExeption("operator>= is not valid for these values!");
	}
}

bool operator==(const Value& lhs, const Value& rhs)
{
	if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::INTEGER) {
		return lhs.intValue == rhs.intValue;
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::INTEGER) {
		return abs(lhs.floatValue - (double)rhs.intValue) < Value::FLOAT_EPSILON;
	}
	else if (lhs.getType() == ValueType::INTEGER && rhs.getType() == ValueType::DBL_FLOAT) {
		return abs((double)lhs.intValue - rhs.floatValue) < Value::FLOAT_EPSILON;
	}
	else if (lhs.getType() == ValueType::DBL_FLOAT && rhs.getType() == ValueType::DBL_FLOAT) {
		return abs(lhs.floatValue - rhs.floatValue) < Value::FLOAT_EPSILON;
	}
	else if (lhs.getType() == ValueType::STRING && rhs.getType() == ValueType::STRING) {
		return lhs.strValue == rhs.strValue;
	}
	else {
		throw InvalidOperatorExeption("operator== is not valid for these values!");
	}
}

bool operator!=(const Value& lhs, const Value& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const Value& value) {
	if (value.getType() == ValueType::INTEGER) {
		stream << value.intValue;
	}
	else if (value.getType() == ValueType::DBL_FLOAT) {
		stream << value.floatValue;
	}
	else if (value.getType() == ValueType::STRING) {
		stream << value.strValue;
	}
	else if (value.getType() == ValueType::NONE) {
		// Do nothing.
	}
	else {
		throw InvalidOperatorExeption("operator<< is not implemented for this type!");
	}

	return stream;
}

InvalidOperatorExeption::InvalidOperatorExeption(std::string what) : runtime_error(what)
{
}
