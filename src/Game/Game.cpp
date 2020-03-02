#include "CircleRenderer.h"
#include "Game.h"
#include "Navigation.h"
#include "SelectionManager.h"

Game::Game()
{
	core = Core::init(500, 500);
}

void Game::start()
{
	std::shared_ptr<Entity> player = core->addEntity();
	std::shared_ptr<SelectionManager> selectionManager =
		player->addComponent<SelectionManager>();

	std::shared_ptr<Entity> unit = core->addEntity();
	selectionManager->addSelectableEntity(unit);
	unit->transform.position = glm::vec3(3.0f, 0.0f, 2.0f);

	std::shared_ptr<CircleRenderer> circle =
		unit->addComponent<CircleRenderer>();

	std::shared_ptr<Navigation> navigation =
		unit->addComponent<Navigation>();

	selectionManager->select(unit);

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
