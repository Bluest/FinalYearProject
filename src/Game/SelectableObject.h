#ifndef SELECTABLE_OBJECT_H
#define SELECTABLE_OBJECT_H

#include <list>

#include "glm/vec2.hpp"

#include "Object.h"

class SelectableObject : public Object
{
public:
	bool isClicked(const glm::ivec2& _clickPosition);

	// TODO: This shouldn't be necessary here, only in Unit
	virtual void move(const std::list<glm::vec2>& _path) {}

	glm::vec2 getPosition();

protected:
	glm::vec2 position;
	float size;
};

#endif // SELECTABLE_OBJECT_H
