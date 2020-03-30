#include "glm/vec2.hpp"

#include "CircleRenderer.h"
#include "Commandable.h"
#include "CommandCreateUnit.h"
#include "CommandManager.h"
#include "CommandMove.h"
#include "CommandStop.h"
#include "InputManager.h"
#include "Game.h"
#include "GameManager.h"
#include "ProtoFactory.h"
#include "Map.h"
#include "Navigation.h"
#include "Selectable.h"
#include "SelectionManager.h"

Game::Game()
{
	core = Core::init(500, 600, 60.0f);

	// initCommands();
	// CommandsList.h?
}

void Game::start()
{
	{
		// UI

		// Player
		std::shared_ptr<Entity> player = core->addEntity();
		//std::shared_ptr<SelectionManager> selectionManager =
		//	player->addComponent<SelectionManager>();
		//std::shared_ptr<CommandManager> commandManager =
		//	player->addComponent<CommandManager>();
		//selectionManager->setCommandManager(commandManager);
		std::shared_ptr<InputManager> inputManager =
			player->addComponent<InputManager>();

		// rightClickCommand[0]: Move
		inputManager->addRightClickCommand(std::make_shared<CommandMove>());
		// rightClickCommand[1]: Attack
		// rightClickCommand[2]: Rally

		// Game board
		std::shared_ptr<Entity> gameBoard = core->addEntity();
		std::shared_ptr<Map> map =
			gameBoard->addComponent<Map>();
		std::shared_ptr<GameManager> gameManager =
			gameBoard->addComponent<GameManager>();
		inputManager->setGameManager(gameManager);

		// Building
		std::shared_ptr<Entity> building = core->addEntity();
		building->transform.position = glm::vec3(1.5f, 0.0f, 17.5f);
		building->transform.scale *= 2.0f;
		building->addTag("Building");
		gameManager->addEntity(building);

		std::shared_ptr<ProtoFactory> protofactory =
			building->addComponent<ProtoFactory>();
		std::shared_ptr<Selectable> buildingSelectable =
			building->addComponent<Selectable>();
		protofactory->setGameManager(gameManager);
		std::shared_ptr<Commandable> buildingCommandable =
			building->addComponent<Commandable>();
		buildingCommandable->addCommand(std::make_shared<CommandCreateUnit>(), 0, 0);

		// Units
		std::shared_ptr<Entity> unit = gameManager->createUnit(glm::vec2(0.0f, 19.0f));
		unit->transform.scale *= 0.8f;

		std::shared_ptr<Entity> unit2 = gameManager->createUnit(glm::vec2(1.0f, 19.0f));
		unit2->transform.scale *= 0.8f;
	}

	core->run();
}
