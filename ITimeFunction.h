#pragma once

namespace sm
{
	class ITimeFunction
	{
	public:
		virtual void step(float dt) = 0;
		virtual float get() const = 0;
	};
}