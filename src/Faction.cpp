#include "Building.h"
#include "Faction.h"
#include "Game.h"
#include "Unit.h"

Faction::Faction(Game* _game)
{
	game = _game;
	energy = 0;
}

void Faction::createUnit(/*Type*/const float& _size, const float& _speed, const glm::vec2& _position)
{
	std::shared_ptr<Unit> unit = std::make_shared<Unit>(_size, _speed, _position);
	units.push_back(unit);
	game->addObject(unit);
}
