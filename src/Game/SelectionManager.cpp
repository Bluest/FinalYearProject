#include "Selectable.h"
#include "SelectionManager.h"
#include "Navigation.h"

void SelectionManager::addSelectableEntity(const std::shared_ptr<Entity>& _entity)
{
	selectableEntities.push_back(_entity);
}

void SelectionManager::onUpdate()
{
	// onStart()?
	std::shared_ptr<Input> input = getCore()->getInput();

	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		// What did I click?

		// Single click, single unit
		selection.clear();
		for (auto it = selectableEntities.begin(); it != selectableEntities.end(); ++it)
		{
			if ((*it)->getComponent<Selectable>()->isClicked(input->mousePosition()))
			{
				selection.push_back(*it);
				break;
			}
		}

		if (!selection.empty()) printf("Selected %p\n", selection.front().get()); else printf("No selection\n");

		//selection.clear();
		//auto blah = gameState->selectObjectAt(input->mousePosition());
		//if (blah != nullptr)
		//{
		//	selection.push_back(blah);
		//	blah->onLeftClick();
		//}
		//
		//if (!selection.empty()) printf("Selected %p\n", selection.front().get()); else printf("No selection\n");
	}

	if (input->mousePress(SDL_BUTTON_RIGHT))
	{
		// What did I click?
		// What do I have selected?

		// Below assumes selection of a unit, clicking the ground

		std::list<glm::vec2> path;
		path.push_back(glm::vec2(getCore()->getInput()->mousePosition()) / nodeSize);
		
		for (auto it = selection.begin(); it != selection.end(); ++it)
		{
			(*it)->getComponent<Navigation>()->setPath(path);

			// TODO: Clean up this line lmao
			// ie. (*it)->move(input->mousePosition()) if Unit has a pointer to Map or something
			//(*it)->move(gameState->getMap()->findPath((*it)->getPosition(), input->mousePosition()));
		}
	}

	if (input->mousePress(SDL_BUTTON_MIDDLE))
	{
		//for (auto it = selection.begin(); it != selection.end(); ++it)
		{
			// if it's a unit, Unit::stop()
			// also depends which object's commands are current
			// command menu is for a unit and has stop? hell yeah
			// command menu is for a building and doesn't? no stoppin'
			//(*it)->stop();
		}
	}
}
