#include "Variable.h"

Variable::Variable()
{
}

Variable::Variable(const std::string& name, Value value) : name(name), value(value)
{
}

std::ostream& operator<<(std::ostream& stream, const Variable& var) {
	stream << var.name << ": " << var.value;
	return stream;
}