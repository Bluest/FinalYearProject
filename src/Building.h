#include "glm/glm.hpp"

class Building
{
public:
	Building(/*Type*/const glm::ivec2& _size, const glm::ivec2& _position);

private:
	glm::ivec2 position;
	glm::ivec2 size;
};
