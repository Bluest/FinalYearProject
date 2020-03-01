#include "GameState.h"
#include "Map.h"
#include "SelectableObject.h"

GameState::GameState(const std::shared_ptr<Map>& _map)
{
	map = _map;
}

void GameState::update()
{
	map->refreshNodes();

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		(*it)->update();
	}
}

void GameState::draw(SDL_Renderer* _renderer)
{
	// Draw
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
	map->drawNodeGrid(_renderer);

	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		(*it)->draw(_renderer);
	}

	SDL_RenderPresent(_renderer);
}

void GameState::addSO(const std::shared_ptr<SelectableObject>& _so)
{
	selectableObjects.push_back(_so);
	objects.push_back(_so);
	// Isn't this the same as Faction::createUnit?
	// It might be cleaner to have it there
}

std::shared_ptr<SelectableObject> GameState::selectObjectAt(const glm::ivec2& _position)
{
	for (auto it = selectableObjects.begin(); it != selectableObjects.end(); ++it)
	{
		// If an object is clicked, select it
		if ((*it)->isClicked(_position))
		{
			return *it;
		}
	}

	return nullptr;
}

std::shared_ptr<Map> GameState::getMap()
{
	return map;
}
