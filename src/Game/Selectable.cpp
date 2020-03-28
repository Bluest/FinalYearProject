#include "Constants.h"
#include "Selectable.h"

bool Selectable::isClicked(const SDL_Point& _clickPosition)
{
	// Translate Entity's position from world space to screen space
	glm::vec3 position = getEntity()->transform.position * nodeSize + nodeSize / 2;
	float size = getEntity()->transform.scale.x * nodeSize;

	SDL_Rect clickBox;
	clickBox.x = int(position.x - size / 2);
	clickBox.y = int(position.z - size / 2);
	clickBox.w = int(size);
	clickBox.h = int(size);

	return SDL_PointInRect(&_clickPosition, &clickBox);
}
