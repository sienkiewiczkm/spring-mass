#include "ConstantFunction.h"

sm::ConstantFunction::ConstantFunction(float constant)
{
	_constant = constant;
}

void sm::ConstantFunction::step(float dt)
{
}

float sm::ConstantFunction::get() const
{
	return _constant;
}
