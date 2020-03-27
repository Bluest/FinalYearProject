#include "Constants.h"
#include "GameManager.h"
#include "ProtoFactory.h"

void ProtoFactory::createUnit()
{
	int randSpawn = rand() % 4;
	glm::vec2 spawnPos;

	switch (randSpawn)
	{
	case 0: spawnPos = glm::vec2(1.0f, 16.0f); break;
	case 1: spawnPos = glm::vec2(2.0f, 16.0f); break;
	case 2: spawnPos = glm::vec2(3.0f, 17.0f); break;
	case 3: spawnPos = glm::vec2(3.0f, 18.0f); break;
	}

	std::shared_ptr<Entity> unit = gameManager.lock()->createUnit();

	unit->transform.position.x = spawnPos.x;
	unit->transform.position.z = spawnPos.y;
	unit->transform.scale *= 0.8f;
}

void ProtoFactory::setGameManager(const std::shared_ptr<GameManager>& _gameManager)
{
	gameManager = _gameManager;
}

void ProtoFactory::onStart()
{
	position = glm::vec2(
		getEntity()->transform.position.x * nodeSize + nodeSize / 2,
		getEntity()->transform.position.z * nodeSize + nodeSize / 2);

	size = getEntity()->transform.scale.x * nodeSize / 2;

	rect = { position.x - size, position.y - size, 2 * size, 2 * size };
	circleSize = size * 0.8f;
}

void ProtoFactory::onDraw(SDL_Renderer* _renderer)
{
	// Fill
	// Square
	SDL_SetRenderDrawColor(_renderer, 128, 0, 0, 255);
	SDL_RenderFillRectF(_renderer, &rect);

	// Circle
	SDL_SetRenderDrawColor(_renderer, 192, 0, 0, 255);
	for (float y = -circleSize; y < circleSize; ++y)
	{
		for (float x = -circleSize; x < circleSize; ++x)
		{
			if (hypotf(x, y) < circleSize)
			{
				SDL_RenderDrawPointF(_renderer, position.x + x, position.y + y);
			}
		}
	}
	
	// Outline
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderDrawRectF(_renderer, &rect);
}
