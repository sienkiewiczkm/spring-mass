#include "MassSpringSimulation.h"

using namespace sm;

MassSpringSimulation::MassSpringSimulation(
	float weightMass,
	float springResilience,
	float initialPosition,
	float massBalancePoint,
	float attenuationFactor,
	float stepLength
)
{
	_weightMass = weightMass;
	_springResilience = springResilience;
	_position = initialPosition;
	_previousPosition = initialPosition;
	_massBalancePoint = massBalancePoint;
	_attenuationFactor = attenuationFactor;
	_step = stepLength;
}

void MassSpringSimulation::step()
{
	float dtSq = _step * _step;

	float resilienceFunction = _springResilience * 
		(_massBalancePoint - _position);

	float outsideForce = 0.0f;

	float previousPositionFactor =
		(_step * _attenuationFactor / (2.0f * _weightMass)) - 1.0f;

	float output = dtSq * resilienceFunction / _weightMass
		+ previousPositionFactor * _previousPosition
		+ (dtSq * outsideForce / _weightMass)
		+ 2.0f * _position;

	float outputFactor = (2.0f * _weightMass) /
		(2.0f * _weightMass + _step * _attenuationFactor);

	float newPosition = outputFactor * output;

	_velocity = (newPosition - _previousPosition) / (2.0f * _step);
	_acceleration = (newPosition - 2.0f * _position + _previousPosition) / dtSq;

	_previousPosition = _position;
	_position = newPosition;
}

float MassSpringSimulation::getPosition() const
{
	return _position;
}

float sm::MassSpringSimulation::getVelocity() const
{
	return _velocity;
}

float MassSpringSimulation::getAcceleration() const
{
	return _acceleration;
}

float MassSpringSimulation::getStep() const
{
	return _step;
}
