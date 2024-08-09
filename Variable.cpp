#include "Variable.h"

Variable::Variable()
{
}

Variable::Variable(const std::string& name, ValueType::Enum valueType) : name(name), valueType(valueType)
{
}
