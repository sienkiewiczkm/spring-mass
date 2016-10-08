#include "MassSpringSimulation.h"

using namespace sm;

MassSpringSimulation::MassSpringSimulation(
	float weightMass,
	float springResilience,
	float initialPosition,
	float initialVelocity,
	float attenuationFactor,
	float stepLength,
	std::shared_ptr<ITimeFunction> massBalancePointFunction,
	std::shared_ptr<ITimeFunction> externalForceFunction
)
{
	_weightMass = weightMass;
	_springResilience = springResilience;
	_position = initialPosition;
	_attenuationFactor = attenuationFactor;
	_step = stepLength;
	_previousPosition = initialPosition - initialVelocity * stepLength;
	_massBalancePointFunction = massBalancePointFunction;
	_externalForceFunction = externalForceFunction;
}

void MassSpringSimulation::step()
{
	_massBalancePointFunction->step(_step);
	_externalForceFunction->step(_step);

	float dtSq = _step * _step;

	_resilienceForce = _springResilience *
		(_massBalancePointFunction->get() - _position);

	float outsideForce = _externalForceFunction->get();

	float previousPositionFactor =
		(_step * _attenuationFactor / (2.0f * _weightMass)) - 1.0f;

	float output = dtSq * _resilienceForce / _weightMass
		+ previousPositionFactor * _previousPosition
		+ (dtSq * outsideForce / _weightMass)
		+ 2.0f * _position;

	float outputFactor = (2.0f * _weightMass) /
		(2.0f * _weightMass + _step * _attenuationFactor);

	float newPosition = outputFactor * output;

	_velocity = (newPosition - _previousPosition) / (2.0f * _step);
	_attenuationForce = -_attenuationFactor * _velocity;

	_acceleration = (newPosition - 2.0f * _position + _previousPosition) / dtSq;

	_previousPosition = _position;
	_position = newPosition;
}

float MassSpringSimulation::getPosition() const
{
	return _position;
}

float MassSpringSimulation::getVelocity() const
{
	return _velocity;
}

float MassSpringSimulation::getAcceleration() const
{
	return _acceleration;
}

float MassSpringSimulation::getResilienceForce() const
{
	return _resilienceForce;
}

float MassSpringSimulation::getAttenuationForce() const
{
	return _attenuationForce;
}

float MassSpringSimulation::getStep() const
{
	return _step;
}
