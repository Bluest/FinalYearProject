#include "CommandCreateUnit.h"
#include "CommandManager.h"

void CommandManager::setCommands(const std::vector<std::vector<std::shared_ptr<Command>>>& _commands)
{
	commands = _commands;
}

void CommandManager::onStart()
{
	input = getCore()->getInput();

	cardPosition.x = 400;
	cardPosition.y = 500;
	cardPosition.w = 100;
	cardPosition.h = 100;
}

void CommandManager::onUpdate()
{
	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		SDL_Point clickPosition = input->mousePosition();
		if (SDL_PointInRect(&clickPosition, &cardPosition))
		{
			// for each command
			// if (SDL_PointInRect(&clickPosition, &commandPosition))
			// command->action();
		}
	}
}

void CommandManager::onDraw(SDL_Renderer* _renderer)
{
	SDL_SetRenderDrawColor(_renderer, 128, 128, 128, 255);
	SDL_RenderFillRect(_renderer, &cardPosition);
}
