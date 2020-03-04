#include "Selectable.h"

bool Selectable::isClicked(const glm::ivec2& _clickPosition)
{
	glm::vec3 position = getEntity()->transform.position * nodeSize;
	float size = getEntity()->transform.scale.x * nodeSize / 2;

	// AABB
	return _clickPosition.x > position.x - size &&
		_clickPosition.x < position.x + size &&
		_clickPosition.y > position.z - size &&
		_clickPosition.y < position.z + size;
}
