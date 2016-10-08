#include "SinusoidalFunction.h"
#include <cmath>

sm::SinusoidalFunction::SinusoidalFunction(
	float amplitude,
	float frequency,
	float shift
) : _timePassed(0.0f)
{
	_amplitude = amplitude;
	_frequency = frequency;
	_shift = shift;
}

void sm::SinusoidalFunction::step(float dt)
{
	_timePassed += dt;
}

float sm::SinusoidalFunction::get() const
{
	return _amplitude * sinf(_frequency * _timePassed + _shift);
}
