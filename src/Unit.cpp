#include "Unit.h"

Unit::Unit(const float& _size, const float& _speed, const glm::vec2& _pos)
{
	size = _size;
	speed = _speed;

	pos = _pos;
	dest = pos;
	step = glm::vec2(0.0f, 0.0f);
	pathIt = path.end();
	updatePathIt = false;
}

bool Unit::isClicked(const glm::ivec2& _click)
{
	// AABB
	return _click.x > pos.x - size &&
		_click.x < pos.x + size &&
		_click.y > pos.y - size &&
		_click.y < pos.y + size;
}

void Unit::move(const std::list<glm::vec2>& _path)
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

		// Handle collisions here
		// If this position overlaps with another unit, push both (or just self) back from the point of collision, but not into a terrain tile
		// What if it's intersecting with multiple units?
		// Its exact previous position will always be available at this point, so worst case, just don't move

		// vvv Could probably use a lerp for this vvv
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
	if (pathIt != path.end())
	{
		SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
		SDL_RenderDrawLineF(_renderer, pos.x, pos.y, path.back().x * 50 + 25, path.back().y * 50 + 25);
		//SDL_RenderDrawLineF(_renderer, pos.x, pos.y, pathIt->x * 50 + 25, pathIt->y * 50 + 25);
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

glm::vec2 Unit::getPos()
{
	return pos;
}

void Unit::moveToPathIt()
{
	dest = { float(pathIt->x * 50 + 25), float(pathIt->y * 50 + 25) };
	
	glm::vec2 delta = dest - pos;
	float distance = hypotf(delta.x, delta.y);
	//float distance = glm::length(delta);
	if (distance > 0)
	{
		step = speed * delta / distance;
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
