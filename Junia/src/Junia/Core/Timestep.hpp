#pragma once

namespace Junia
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : time(time) { }

		float GetSeconds() const { return time; }
		float GetMilliseconds() const { return time * 1000.0f; }

	private:
		float time;
	};
}
