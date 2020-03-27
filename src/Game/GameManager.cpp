#include "CircleRenderer.h"
#include "CommandStop.h"
#include "GameManager.h"
#include "Map.h"
#include "Navigation.h"
#include "Selectable.h"

void GameManager::onInit()
{
	map = getEntity()->getComponent<Map>();
}

void GameManager::addSelectable(const std::shared_ptr<Selectable>& _selectable)
{
	selectables.push_back(_selectable);
}

std::shared_ptr<Entity> GameManager::createUnit(const glm::vec2& _position)
{
	std::shared_ptr<Entity> unit = getCore()->addEntity();
	unit->transform.position.x = _position.x;
	unit->transform.position.z = _position.y;

	std::shared_ptr<Selectable> selectable =
		unit->addComponent<Selectable>();
	selectables.push_back(selectable);
	selectable->addTag(Selectable::Tag::UNIT);
	selectable->addCommand(std::make_shared<CommandStop>(), 0, 1);

	std::shared_ptr<Navigation> navigation =
		unit->addComponent<Navigation>();
	navigation->setMap(map);

	std::shared_ptr<CircleRenderer> circleRenderer =
		unit->addComponent<CircleRenderer>();

	return unit;
}

std::list<std::shared_ptr<Selectable>> GameManager::getSelectables()
{
	return selectables;
}
