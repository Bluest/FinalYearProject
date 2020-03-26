#include "CircleRenderer.h"
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
	std::shared_ptr<GameManager> gameManager =
		gameBoard->addComponent<GameManager>();
	inputManager->setGameManager(gameManager);
	std::shared_ptr<Map> map =
		gameBoard->addComponent<Map>();

	// Building
	std::shared_ptr<Entity> building = core->addEntity();
	building->transform.position = glm::vec3(1.5f, 0.0f, 17.5f);
	building->transform.scale *= 2.0f;

	std::shared_ptr<ProtoFactory> protofactory =
		building->addComponent<ProtoFactory>();
	std::shared_ptr<Selectable> buildingSelectable =
		building->addComponent<Selectable>();
	gameManager->addSelectable(buildingSelectable);
	buildingSelectable->addCommand(std::make_shared<CommandCreateUnit>(), 0, 0);

	// Units
	std::shared_ptr<Entity> unit = core->addEntity();
	unit->transform.position = glm::vec3(0.0f, 0.0f, 19.0f);
	unit->transform.scale *= 0.8f;

	std::shared_ptr<Selectable> selectable =
		unit->addComponent<Selectable>();
	gameManager->addSelectable(selectable);
	selectable->addCommand(std::make_shared<CommandStop>(), 0, 1);
	std::shared_ptr<Navigation> navigation =
		unit->addComponent<Navigation>();
	navigation->setMap(map);
	std::shared_ptr<CircleRenderer> circle =
		unit->addComponent<CircleRenderer>();

	std::shared_ptr<Entity> unit2 = core->addEntity();
	unit2->transform.position = glm::vec3(1.0f, 0.0f, 19.0f);
	unit2->transform.scale *= 0.8f;

	std::shared_ptr<Selectable> selectable2 =
		unit2->addComponent<Selectable>();
	gameManager->addSelectable(selectable2);
	selectable2->addCommand(std::make_shared<CommandStop>(), 0, 1);
	std::shared_ptr<Navigation> navigation2 =
		unit2->addComponent<Navigation>();
	navigation2->setMap(map);
	std::shared_ptr<CircleRenderer> circle2 =
		unit2->addComponent<CircleRenderer>();

	core->run();
}
