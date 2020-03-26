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

	selection = std::make_shared<std::list<std::shared_ptr<Selectable>>>();
	commandManager->setSelection(selection);
}

void SelectionManager::onUpdate()
{
	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		// What did I click?

		// Single click, single unit
		std::list<std::shared_ptr<Selectable>> selectables = gameManager->getSelectables();
		for (auto it = selectables.begin(); it != selectables.end(); ++it)
		{
			// If an object is clicked, select it
			if ((*it)->isClicked(input->mousePosition()))
			{
				selection->clear();
				selection->push_back(*it);
				commandManager->setCommands((*it)->getCommands());
				break;
			}
		}
	}
}
