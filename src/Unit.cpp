#include "Unit.h"
#include "Node.h"

Unit::Unit(float _size, float _speed, float _posX, float _posY)
{
	size = _size;
	speed = _speed;

	pos = { _posX, _posY };
	pathIt = path.begin();
}

void Unit::move(const std::list<std::shared_ptr<Node>>& _path)
{
	path = _path;
	pathIt = path.begin();
}

void Unit::stop()
{
	path.clear();
	pathIt = path.end();
}

void Unit::update()
{
	if (pathIt != path.end())
	{
		pos.x = float((*pathIt)->x * 50 + 25);
		pos.y = float((*pathIt)->y * 50 + 25);
		std::advance(pathIt, 1);
	
		/*pos.x += step.x;
		pos.y += step.y;
	
		if (step.x > 0.0f) { if (pos.x > dest.x) moving = false; }
		else if (step.x < 0.0f) { if (pos.x < dest.x) moving = false; }
	
		if (step.y > 0.0f) { if (pos.y > dest.y) moving = false; }
		else if (step.y < 0.0f) { if (pos.y < dest.y) moving = false; }
	
		if (!moving)
		{
			pos.x = dest.x;
			pos.y = dest.y;
		}*/
	}
}

void Unit::draw(SDL_Renderer* _renderer)
{
	// Path
	if (pathIt != path.end())
	{
		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(_renderer, int(pos.x), int(pos.y), (*pathIt)->x * 50 + 25, (*pathIt)->y * 50 + 25);
	}

	// Fill
	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	for (float y = -size; y < size; ++y)
	{
		for (float x = -size; x < size; ++x)
		{
			if (hypotf(x, y) < size)
			{
				SDL_RenderDrawPointF(_renderer, pos.x + x, pos.y + y);
			}
		}
	}

	// Outline
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	for (float t = 0; t < 2 * M_PI; t += 1.0f / size)
	{
		SDL_RenderDrawPointF(_renderer, pos.x + size * sinf(t), pos.y + size * cosf(t));
	}
}

vec2f Unit::getPos()
{
	return pos;
}
