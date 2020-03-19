#include "GameManager.h"

void GameManager::addSelectable(const std::shared_ptr<Selectable>& _selectable)
{
	selectables.push_back(_selectable);
}

std::list<std::shared_ptr<Selectable>> GameManager::getSelectables()
{
	return selectables;
}
