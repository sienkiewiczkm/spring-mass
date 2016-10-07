#pragma once

namespace sm
{
	class MassSpringSimulation
	{
	public:
		MassSpringSimulation(
			float weightMass,
			float springResilience,
			float initialPosition,
			float massBalancePoint,
			float attenuationFactor,
			float stepLength
		);

		void step();

		float getPosition() const;
		float getVelocity() const;
		float getAcceleration() const;

		float getStep() const;

	private:
		float _weightMass;
		float _springResilience;
		float _position;
		float _previousPosition;
		float _massBalancePoint;
		float _attenuationFactor;
		float _step;
		float _velocity;
		float _acceleration;
	};
}