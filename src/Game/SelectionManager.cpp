#include "CommandManager.h"
#include "Constants.h"
#include "GameManager.h"
#include "Selectable.h"
#include "SelectionManager.h"
#include "Navigation.h"

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
}

void SelectionManager::onUpdate()
{
	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		// What did I click?

		// Single click, single unit
		selection.clear();
		std::list<std::shared_ptr<Selectable>> selectables = gameManager->getSelectables();
		for (auto it = selectables.begin(); it != selectables.end(); ++it)
		{
			// If an object is clicked, select it
			if ((*it)->isClicked(input->mousePosition()))
			{
				selection.push_back(*it);
				commandManager->setCommands((*it)->getCommands());
				commandManager->setTarget(*it);
				// set Command targets
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
	//
	//if (input->mousePress(SDL_BUTTON_MIDDLE))
	//{
	//	for (auto it = selection.begin(); it != selection.end(); ++it)
	//	{
	//		// if it's a unit, Unit::stop()
	//		// also depends which object's commands are current
	//		// command menu is for a unit and has stop? hell yeah
	//		// command menu is for a building and doesn't? no stoppin'
	//
	//		// If the entity has a Navigation component, Navigation::stop
	//		if ((*it)->getComponent<Navigation>())
	//		{
	//			(*it)->getComponent<Navigation>()->stop();
	//		}
	//	}
	//}
}
