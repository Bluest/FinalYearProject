#include "Building.h"
#include "Faction.h"
#include "Unit.h"

void Faction::createUnit(/*Type*/const float& _size, const float& _speed, const glm::vec2& _position)
{
	units.emplace_back(std::make_shared<Unit>(_size, _speed, _position));
}
