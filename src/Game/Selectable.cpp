#include "Selectable.h"

bool Selectable::isClicked(const glm::ivec2& _clickPosition)
{
	// Translate Entity's position from world space to screen space
	glm::vec3 position = getEntity()->transform.position * nodeSize + nodeSize / 2;
	float size = getEntity()->transform.scale.x * nodeSize / 2;

	// AABB
	return _clickPosition.x > position.x - size &&
		_clickPosition.x < position.x + size &&
		_clickPosition.y > position.z - size &&
		_clickPosition.y < position.z + size;
}
