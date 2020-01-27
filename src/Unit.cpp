#include "Unit.h"

Unit::Unit(float _size, float _speed, float _posX, float _posY)
{
	size = _size;
	speed = _speed;

	moving = false;
	pos = { _posX, _posY };
	dest = { _posX, _posY };
	step = { NULL, NULL };
}

void Unit::draw(SDL_Renderer* _renderer)
{
	if (moving)
	{
		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(_renderer,
			static_cast<int>(pos.x),
			static_cast<int>(pos.y),
			static_cast<int>(dest.x),
			static_cast<int>(dest.y));
	}

	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	for (float t = 0; t < 2 * M_PI; t += 1.0f / size)
	{
		SDL_RenderDrawPointF(_renderer, pos.x + size * sinf(t), pos.y + size * cosf(t));
	}
}

void Unit::update()
{
	if (moving)
	{
		pos.x += step.x;
		pos.y += step.y;

		if (step.x > 0.0f) { if (pos.x > dest.x) moving = false; }
		else if (step.x < 0.0f) { if (pos.x < dest.x) moving = false; }

		if (step.y > 0.0f) { if (pos.y > dest.y) moving = false; }
		else if (step.y < 0.0f) { if (pos.y < dest.y) moving = false; }

		if (!moving)
		{
			pos.x = dest.x;
			pos.y = dest.y;
		}
	}
}

void Unit::move()
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	dest.x = static_cast<float>(x);
	dest.y = static_cast<float>(y);

	vec2f delta = { dest.x - pos.x, dest.y - pos.y };
	float distance = hypotf(delta.x, delta.y);
	if (distance > 0)
	{
		step.x = speed * delta.x / distance;
		step.y = speed * delta.y / distance;
		moving = true;
	}
}

void Unit::stop()
{
	moving = false;
}
