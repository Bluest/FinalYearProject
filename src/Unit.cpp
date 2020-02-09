#include "Unit.h"
#include "Node.h" // Remove when path is replaced with a list of vec2

Unit::Unit(float _size, float _speed, float _posX, float _posY)
{
	size = _size;
	speed = _speed;

	pos = { _posX, _posY };
	dest = { _posX, _posY };
	step = { 0.0f, 0.0f };
	pathIt = path.end();
	updatePathIt = false;
}

void Unit::move(const std::list<std::shared_ptr<Node>>& _path)
{
	if (!_path.empty())
	{
		path = _path;
		pathIt = path.begin();
		moveToPathIt();
	}
}

void Unit::stop()
{
	dest = { pos.x, pos.y };
	step = { 0.0f, 0.0f };
	path.clear();
	pathIt = path.end();
}

void Unit::update()
{
	if (pathIt != path.end())
	{
		pos.x += step.x;
		pos.y += step.y;
	
		// Instead of these if elses below, perhaps track progress from node to node with a scalar?
		// Also so that the remainder of the scalar can carry over to moving towards the next node this frame
		// Currently if the step overshoots, the unit snaps back to that node, causing slight stuttering

		// Moving right or left
		if (step.x > 0.0f) { if (pos.x > dest.x) updatePathIt = true; }
		else if (step.x < 0.0f) { if (pos.x < dest.x) updatePathIt = true; }
	
		// Moving down or up
		if (step.y > 0.0f) { if (pos.y > dest.y) updatePathIt = true; }
		else if (step.y < 0.0f) { if (pos.y < dest.y) updatePathIt = true; }
	
		if (updatePathIt)
		{
			pos.x = dest.x;
			pos.y = dest.y;

			std::advance(pathIt, 1);
			if (pathIt != path.end())
			{
				moveToPathIt();
			}

			updatePathIt = false;
		}
	}
}

void Unit::draw(SDL_Renderer* _renderer)
{
	// Path
	//if (pathIt != path.end())
	//{
	//	SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
	//	SDL_RenderDrawLine(_renderer, int(pos.x), int(pos.y), (*pathIt)->x * 50 + 25, (*pathIt)->y * 50 + 25);
	//}

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

void Unit::moveToPathIt()
{
	dest = { float((*pathIt)->x * 50 + 25), float((*pathIt)->y * 50 + 25) };

	vec2f delta = { dest.x - pos.x, dest.y - pos.y };
	float distance = hypotf(delta.x, delta.y);
	if (distance > 0)
	{
		step.x = speed * delta.x / distance;
		step.y = speed * delta.y / distance;
	}
	else
	{
		std::advance(pathIt, 1);
		if (pathIt != path.end())
		{
			moveToPathIt();
		}
	}
}
