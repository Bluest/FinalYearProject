#include "CommandManager.h"

void CommandManager::onStart()
{
	input = getCore()->getInput();
}

void CommandManager::onUpdate()
{
	if (input->keyPress(SDLK_1))
	{
		printf("1\n");
	}
}
