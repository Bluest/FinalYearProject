#include "CircleRenderer.h"
#include "Game.h"
#include "Map.h"
#include "Navigation.h"
#include "Selectable.h"
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

	std::shared_ptr<Entity> environment = core->addEntity();
	std::shared_ptr<Map> map =
		environment->addComponent<Map>();

	std::shared_ptr<Entity> unit = core->addEntity();
	selectionManager->addSelectableEntity(unit);
	unit->transform.position = glm::vec3(3.0f, 0.0f, 1.0f);
	unit->transform.scale *= 0.8f;

	std::shared_ptr<Selectable> selectable =
		unit->addComponent<Selectable>();
	std::shared_ptr<Navigation> navigation =
		unit->addComponent<Navigation>();
	navigation->setMap(map);
	std::shared_ptr<CircleRenderer> circle =
		unit->addComponent<CircleRenderer>();

	std::shared_ptr<Entity> unit2 = core->addEntity();
	selectionManager->addSelectableEntity(unit2);
	unit2->transform.position = glm::vec3(5.0f, 0.0f, 2.0f);
	unit2->transform.scale *= 0.8f;

	std::shared_ptr<Selectable> selectable2 =
		unit2->addComponent<Selectable>();
	std::shared_ptr<Navigation> navigation2 =
		unit2->addComponent<Navigation>();
	navigation2->setMap(map);
	std::shared_ptr<CircleRenderer> circle2 =
		unit2->addComponent<CircleRenderer>();

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
