#include "glm/vec2.hpp"

#include "Game.h"
#include "GameState.h"
#include "Map.h"
#include "Player.h"

#include "Unit.h"
#include "Building.h"
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
	gameState->addSO(std::make_shared<ProtoFactory>(50.0f, glm::vec2(50.0f, 450.0f), gameState));

	while (player->handleInput())
	{
		gameState->update(); // deltaTime in Game or GameState?
		gameState->draw(renderer);

		// TODO: Time Class
		SDL_Delay(16);
	}
}
