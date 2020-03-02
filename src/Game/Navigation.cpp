#include "Navigation.h"

void Navigation::setPath(const std::list<glm::vec2>& _path)
{
	if (!_path.empty())
	{
		path = _path;
	}
}

void Navigation::onUpdate()
{
	if (!path.empty())
	{
		glm::vec3 pos = getEntity()->transform.position;
		printf("x: %f, y: %f, z: %f\n", pos.x, pos.y, pos.z);
		getEntity()->transform.position.x = path.front().x;
		getEntity()->transform.position.z = path.front().y;
		path.clear();
	}
}
