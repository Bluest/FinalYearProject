#include "Game.h"
#include "GameState.h"
#include "Map.h"
#include "Player.h"

Game::Game()
{
	core = Core::init(500, 500);

	map = std::make_shared<Map>();
	gameState = std::make_shared<GameState>(map);
	player = std::make_shared<Player>(gameState);
}

void Game::start()
{
	std::shared_ptr<Entity> test = core->addEntity();
	std::shared_ptr<Component> comp = test->addComponent<Component>();

	core->run();
}

/*void Game::run()
{
	gameState->addSO(std::make_shared<ProtoFactory>(50.0f, glm::vec2(50.0f, 450.0f), gameState));

	while (player->handleInput())
	{
		gameState->update(); // deltaTime in Game or GameState?
		gameState->draw(renderer);

		// TODO: Time Class
		SDL_Delay(16);
	}
}*/
