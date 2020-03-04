#include "Map.h"
#include "Navigation.h"

void Navigation::setMap(const std::shared_ptr<Map>& _map)
{
	map = _map;
}

void Navigation::move(const glm::vec2& _destination)
{
	path = map->findPath(position, _destination);
}

void Navigation::onStart()
{
	// This is mostly for convenience
	// only worth it if position gets called a lot in onUpdate
	position.x = getEntity()->transform.position.x;
	position.y = getEntity()->transform.position.z;
}

void Navigation::onUpdate()
{
	if (!path.empty())
	{
		position.x = path.front().x;
		position.y = path.front().y;
		path.pop_front();

		updateEntityPosition();
	}
}

void Navigation::updateEntityPosition()
{
	getEntity()->transform.position.x = position.x;
	getEntity()->transform.position.z = position.y;
}
