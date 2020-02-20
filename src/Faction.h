#include <list>
#include <memory>

#include "glm/glm.hpp"

class Building;
class Game;
class Unit;

class Faction
{
public:
	Faction(Game* _game);

	void createUnit(/*Type*/const float& _size, const float& _speed, const glm::vec2& _position);

private:
	Game* game;

	int energy;
	std::list<std::shared_ptr<Unit>> units;
	std::list<std::shared_ptr<Building>> buildings;

	std::list<std::shared_ptr<Unit>> unitSelection;
};
