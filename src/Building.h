#include "glm/vec2.hpp"

#include "SelectableObject.h"

class Building : public SelectableObject
{
public:
	Building(/*Type*/const glm::ivec2& _size, const glm::ivec2& _position);

private:
	glm::ivec2 position;
	glm::ivec2 size;
};
