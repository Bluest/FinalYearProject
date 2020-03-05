#include "Time.h"

Time::Time(const float& _fpsCap)
{
	target = 1.0f / _fpsCap;
	delta = target;
	prev = 0.0f;
	curr = 0.0f;
}

void Time::start()
{
	prev = float(SDL_GetTicks());
}

void Time::tick()
{
	curr = float(SDL_GetTicks());
	delta = (curr - prev) / 1000.0f;
	prev = curr;

	if (delta < target)
	{
		SDL_Delay(Uint32((target - delta) * 1000.0f));
	}
}

float Time::getDelta()
{
	return delta;
}
