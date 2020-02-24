// This file and Unit.h may need include guards

#include "glm/vec2.hpp"

#include "SelectableObject.h"

class Building : public SelectableObject
{
public:
	Building(/*Type*/const glm::ivec2& _size, const glm::ivec2& _position);

protected:
	glm::ivec2 position;
	glm::ivec2 size;
};
