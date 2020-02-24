#include "glm/vec2.hpp"

#include "Game.h"
#include "GameState.h"
#include "Map.h"
#include "Player.h"

#include "Unit.h"
#include "ProtoFactory.h"

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(500, 500, 0, &window, &renderer);

	map = std::make_shared<Map>();
	gameState = std::make_shared<GameState>(map);
	player = std::make_shared<Player>(gameState);
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	gameState->addSO(std::make_shared<Unit>(20.0f, 5.0f, glm::vec2(75.0f, 475.0f)));
	gameState->addSO(std::make_shared<Unit>(20.0f, 5.0f, glm::vec2(25.0f, 475.0f)));
	gameState->addSO(std::make_shared<Unit>(20.0f, 5.0f, glm::vec2(25.0f, 425.0f)));
	// world space should definitely be { 3.0f, 9.0f } instead of { 75.0f, 475.0f }
	// as soon as OpenGL rendering is integrated

	while (player->handleInput())
	{
		gameState->update(); // deltaTime in Game or GameState?
		gameState->draw(renderer);

		// TODO: Time Class
		SDL_Delay(16);
	}
}
