#pragma once

#include "ITimeFunction.h"

namespace sm
{
	class SinusoidalFunction : public ITimeFunction
	{
	public:
		SinusoidalFunction(float amplitude, float multipler, float shift);
		void step(float dt);
		float get() const;

	private:
		float _timePassed;
		float _amplitude;
		float _frequency;
		float _shift;
	};
}