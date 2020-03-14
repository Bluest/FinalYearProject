#include "CommandManager.h"

void CommandManager::onStart()
{
	input = getCore()->getInput();
}

void CommandManager::onUpdate()
{
	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		SDL_Point clickPosition = input->mousePosition();
		printf("%i, %i\n", clickPosition.x, clickPosition.y);
	}
}
