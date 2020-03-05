#include "GameState.h"
#include "ProtoFactory.h"

ProtoFactory::ProtoFactory(/*Type*/const float& _size, const glm::vec2& _position, const std::shared_ptr<GameState>& _gameState) : Building(_size, _position)
{
	gameState = _gameState;
	rect = { _position.x - _size, _position.y - _size, 2 * _size, 2 * _size };
}

void ProtoFactory::draw(SDL_Renderer* _renderer)
{
	float circleSize = size * 0.8f;

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

void ProtoFactory::onLeftClick()
{
	int randSpawn = rand() % 4;
	glm::vec2 spawnPos;

	switch (randSpawn)
	{
	case 0: spawnPos = glm::vec2(25.0f, 375.0f); break;
	case 1: spawnPos = glm::vec2(75.0f, 375.0f); break;
	case 2: spawnPos = glm::vec2(125.0f, 425.0f); break;
	case 3: spawnPos = glm::vec2(125.0f, 475.0f); break;
	}

	//gameState.lock()->addSO(std::make_shared<Unit>(20.0f, 5.0f, spawnPos));
	// TODO: world space should definitely be { 3.0f, 9.0f } instead of { 75.0f, 475.0f }
	// as soon as OpenGL rendering is integrated
}
