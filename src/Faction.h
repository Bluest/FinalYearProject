#include <list>
#include <memory>

#include "glm/glm.hpp"

class Unit;
class Building;

class Faction
{
public:
	void createUnit(/*Type*/const float& _size, const float& _speed, const glm::vec2& _position);

private:
	int energy;
	std::list<std::shared_ptr<Unit>> units;
	std::list<std::shared_ptr<Building>> buildings;
};
