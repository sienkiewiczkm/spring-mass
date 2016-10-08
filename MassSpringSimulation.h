#pragma once

#include "ITimeFunction.h"

#include <memory>

namespace sm
{
	class MassSpringSimulation
	{
	public:
		MassSpringSimulation(
			float weightMass,
			float springResilience,
			float initialPosition,
			float initialVelocity,
			float attenuationFactor,
			float stepLength,
			std::shared_ptr<ITimeFunction> massBalancePointFunction,
			std::shared_ptr<ITimeFunction> externalForceFunction
		);

		void step();

		float getPosition() const;
		float getVelocity() const;
		float getAcceleration() const;
		float getResilienceForce() const;
		float getAttenuationForce() const;

		float getStep() const;

	private:
		float _weightMass;
		float _springResilience;
		float _position;
		float _previousPosition;
		float _attenuationFactor;
		float _step;

		float _velocity;
		float _acceleration;
		float _resilienceForce;
		float _attenuationForce;

		std::shared_ptr<ITimeFunction> _massBalancePointFunction;
		std::shared_ptr<ITimeFunction> _externalForceFunction;
	};
}