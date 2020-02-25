#ifndef BUILDING_H
#define BUILDING_H

#include "glm/vec2.hpp"

#include "SelectableObject.h"

class Building : public SelectableObject
{
public:
	Building(/*Type*/const float& _size, const glm::vec2& _position);
};

#endif // BUILDING_H
