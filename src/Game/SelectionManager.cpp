#include "Commandable.h"
#include "CommandManager.h"
#include "GameManager.h"
#include "Selectable.h"
#include "SelectionManager.h"

void SelectionManager::setCommandManager(const std::shared_ptr<CommandManager>& _commandManager)
{
	commandManager = _commandManager;
}

void SelectionManager::setGameManager(const std::shared_ptr<GameManager>& _gameManager)
{
	gameManager = _gameManager;
}

void SelectionManager::onStart()
{
	input = getCore()->getInput();

	selection = std::make_shared<std::list<std::shared_ptr<Entity>>>();
	commandManager->setSelection(selection);
}

void SelectionManager::onUpdate()
{
	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		// What did I click?

		// Single click, single unit
		std::list<std::shared_ptr<Entity>> gameEntities = gameManager->getEntities();
		for (auto it = gameEntities.begin(); it != gameEntities.end(); ++it)
		{
			// If an object is clicked, select it
			if ((*it)->getComponent<Selectable>()->isClicked(input->mousePosition()))
			{
				selection->clear();
				selection->push_back(*it);
				commandManager->setCommands((*it)->getComponent<Commandable>()->getCommands());
				break;
			}
		}
	}
}
