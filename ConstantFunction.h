#pragma once

#include "ITimeFunction.h"

namespace sm
{
	class ConstantFunction : public ITimeFunction
	{
	public:
		ConstantFunction(float constant);

		void step(float dt);
		float get() const;

	private:
		float _constant;
	};
}