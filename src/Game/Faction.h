#include <list>
#include <memory>

#include "glm/vec2.hpp"

class Building;
class Unit;

class Faction
{
public:
	void createUnit(/*Type*/const float& _size, const float& _speed, const glm::vec2& _position);

private:
	int energy = 0;
	std::list<std::shared_ptr<Unit>> units;
	std::list<std::shared_ptr<Building>> buildings;
};
