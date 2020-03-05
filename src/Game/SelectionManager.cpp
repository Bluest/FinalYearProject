#include "Selectable.h"
#include "SelectionManager.h"
#include "Navigation.h"

void SelectionManager::addSelectableEntity(const std::shared_ptr<Entity>& _entity)
{
	selectableEntities.push_back(_entity);
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
		for (auto it = selectableEntities.begin(); it != selectableEntities.end(); ++it)
		{
			// If an object is clicked, select it
			if ((*it)->getComponent<Selectable>()->isClicked(input->mousePosition()))
			{
				selection.push_back(*it);
				//(*it)->onLeftClick();
				break;
			}
		}

		if (!selection.empty()) printf("Selected %p\n", selection.front().get()); else printf("No selection\n");
	}

	if (input->mousePress(SDL_BUTTON_RIGHT))
	{
		// What did I click?
		// What do I have selected?

		// if mousePosition isn't over an ally or enemy unit (so it's over the ground)
		glm::vec2 worldPosition = (glm::vec2(input->mousePosition()) - nodeSize / 2) / nodeSize;
		// "move here" animation on ground

		// Attempt to move selected units to the position clicked
		for (auto it = selection.begin(); it != selection.end(); ++it)
		{
			(*it)->getComponent<Navigation>()->move(worldPosition);
		}
	}

	if (input->mousePress(SDL_BUTTON_MIDDLE))
	{
		for (auto it = selection.begin(); it != selection.end(); ++it)
		{
			// if it's a unit, Unit::stop()
			// also depends which object's commands are current
			// command menu is for a unit and has stop? hell yeah
			// command menu is for a building and doesn't? no stoppin'
			(*it)->getComponent<Navigation>()->stop();
		}
	}
}
