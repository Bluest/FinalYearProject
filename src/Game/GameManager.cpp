#include "CircleRenderer.h"
#include "Commandable.h"
#include "CommandStop.h"
#include "CommandUnitRightClick.h"
#include "GameManager.h"
#include "Map.h"
#include "Navigation.h"
#include "Selectable.h"

void GameManager::onInit()
{
	map = getEntity()->getComponent<Map>();
}

void GameManager::addEntity(const std::shared_ptr<Entity>& _entity)
{
	entities.push_back(_entity);
}

std::shared_ptr<Entity> GameManager::createUnit(const glm::vec2& _position)
{
	std::shared_ptr<Entity> unit = getCore()->addEntity();
	unit->transform.position.x = _position.x;
	unit->transform.position.z = _position.y;
	unit->addTag("Unit");

	std::shared_ptr<Selectable> selectable =
		unit->addComponent<Selectable>();

	std::shared_ptr<Commandable> commandable =
		unit->addComponent<Commandable>();
	commandable->addCommand(std::make_shared<CommandStop>(), 0, 1);
	commandable->setRightClickCommand(std::make_shared<CommandUnitRightClick>());

	std::shared_ptr<Navigation> navigation =
		unit->addComponent<Navigation>();
	navigation->setMap(map);

	std::shared_ptr<CircleRenderer> circleRenderer =
		unit->addComponent<CircleRenderer>();

	entities.push_back(unit);

	return unit;
}

std::shared_ptr<Entity> GameManager::getEntityAt(const SDL_Point& _position)
{
	for (auto it = entities.begin(); it != entities.end(); ++it)
	{
		if ((*it)->getComponent<Selectable>()->isClicked(_position))
		{
			return *it;
		}
	}

	return nullptr;
}

void GameManager::destroyEntity(const std::shared_ptr<Entity>& _entity)
{
	entities.remove(_entity);
	_entity->destroy();
}

std::list<std::shared_ptr<Entity>> GameManager::getEntities()
{
	return entities;
}
