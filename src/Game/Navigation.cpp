#include "Map.h"
#include "Navigation.h"

void Navigation::onInit()
{
	speed = 5.0f;
	position.x = getEntity()->transform.position.x;
	position.y = getEntity()->transform.position.z;
	step = glm::vec2(0.0f, 0.0f);
	waypoint = path.begin();
	nextWaypoint = false;
}

void Navigation::move(const glm::vec2& _destination)
{
	std::list<glm::vec2> newPath = map.lock()->findPath(position, _destination);

	if (!newPath.empty())
	{
		path = newPath;
		waypoint = path.begin();
		moveToWaypoint();
	}
}

void Navigation::stop()
{
	step = glm::vec2(0.0f, 0.0f);
	path.clear();
	waypoint = path.begin();
}

void Navigation::setMap(const std::weak_ptr<Map>& _map)
{
	map = _map;
}

void Navigation::onUpdate()
{
	if (!path.empty())
	{
		position += step * getCore()->getDeltaTime();

		// Check for collisions
		// If this position overlaps with another unit, push both (or just self) back from the point of collision, but not into a terrain tile
		// What if it's intersecting with multiple units?
		// Its exact previous position will always be available at this point, so worst case, just don't move

		// vvv Could probably use a lerp for this vvv
		// Instead of these if elses below, perhaps track progress from node to node with a scalar?
		// Also so that the remainder of the scalar can carry over to moving towards the next node this frame
		// Currently if the step overshoots, the unit snaps back to that node, causing slight stuttering

		// Moving right or left
		if (step.x > 0.0f) { if (position.x > waypoint->x) nextWaypoint = true; }
		else if (step.x < 0.0f) { if (position.x < waypoint->x) nextWaypoint = true; }

		// Moving down or up
		if (step.y > 0.0f) { if (position.y > waypoint->y) nextWaypoint = true; }
		else if (step.y < 0.0f) { if (position.y < waypoint->y) nextWaypoint = true; }

		if (nextWaypoint)
		{
			position = *waypoint;

			++waypoint;
			path.pop_front();

			if (waypoint != path.end())
			{
				moveToWaypoint();
			}

			nextWaypoint = false;
		}

		updateEntityPosition();
	}
}

void Navigation::moveToWaypoint()
{
	glm::vec2 delta = *waypoint - position;
	float distance = hypotf(delta.x, delta.y);
	//float distance = glm::length(delta);

	if (distance > 0)
	{
		step = speed * delta / distance;
	}
}

void Navigation::updateEntityPosition()
{
	getEntity()->transform.position.x = position.x;
	getEntity()->transform.position.z = position.y;
}
