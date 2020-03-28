#include "CircleRenderer.h"
#include "Commandable.h"
#include "CommandStop.h"
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

	std::shared_ptr<Selectable> selectable =
		unit->addComponent<Selectable>();
	selectable->addTag(Selectable::Tag::UNIT);

	std::shared_ptr<Commandable> commandable =
		unit->addComponent<Commandable>();
	commandable->addCommand(std::make_shared<CommandStop>(), 0, 1);

	std::shared_ptr<Navigation> navigation =
		unit->addComponent<Navigation>();
	navigation->setMap(map);

	std::shared_ptr<CircleRenderer> circleRenderer =
		unit->addComponent<CircleRenderer>();

	entities.push_back(unit);

	return unit;
}

std::list<std::shared_ptr<Entity>> GameManager::getEntities()
{
	return entities;
}
