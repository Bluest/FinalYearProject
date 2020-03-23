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

	//if (input->mousePress(SDL_BUTTON_RIGHT))
	//{
	//	// What did I click?
	//	// What do I have selected?
	//
	//	// if mousePosition isn't over an enemy unit (so it's not an attack command)
	//	glm::vec2 worldPosition = (glm::vec2(input->mousePosition().x, input->mousePosition().y) - nodeSize / 2) / nodeSize;
	//	// "move here" animation on ground
	//
	//	// Attempt to move selected units to the position clicked
	//	for (auto it = selection.begin(); it != selection.end(); ++it)
	//	{
	//		// If the entity has a Navigation component, Navigation::move to click position
	//		if ((*it)->getComponent<Navigation>())
	//		{
	//			(*it)->getComponent<Navigation>()->move(worldPosition);
	//		}
	//	}
	//}
}
