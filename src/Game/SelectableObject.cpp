#include "SelectableObject.h"

bool SelectableObject::isClicked(const glm::ivec2& _clickPosition)
{
	// AABB
	return _clickPosition.x > position.x - size &&
		_clickPosition.x < position.x + size &&
		_clickPosition.y > position.y - size &&
		_clickPosition.y < position.y + size;
}

glm::vec2 SelectableObject::getPosition()
{
	return position;
}
