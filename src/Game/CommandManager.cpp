#include "CommandCreateUnit.h"
#include "CommandManager.h"

void CommandManager::setCommands(const std::vector<std::vector<std::shared_ptr<Command>>>& _commands)
{
	commands = _commands;

	commands.resize(slotRows);
	for (size_t y = 0; y < slotRows; ++y)
	{
		commands[y].resize(slotColumns);
	}
}

void CommandManager::onStart()
{
	input = getCore()->getInput();

	cardPosition.x = 350;
	cardPosition.y = 500;
	cardPosition.w = 150;
	cardPosition.h = 100;

	commandPosition.w = 50;
	commandPosition.h = 50;
}

void CommandManager::onUpdate()
{
	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		SDL_Point clickPosition = input->mousePosition();
		if (SDL_PointInRect(&clickPosition, &cardPosition))
		{
			for (size_t y = 0; y < commands.size(); ++y)
			{
				for (size_t x = 0; x < commands[y].size(); ++x)
				{
					if (commands[y][x])
					{
						commandPosition.x = x * commandPosition.w + cardPosition.x;
						commandPosition.y = y * commandPosition.h + cardPosition.y;

						if (SDL_PointInRect(&clickPosition, &commandPosition))
						{
							commands[y][x]->action();
						}
					}
				}
			}
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

	SDL_SetRenderDrawColor(_renderer, 192, 192, 192, 255);
	for (size_t y = 0; y < slotRows; ++y)
	{
		for (size_t x = 0; x < slotColumns; ++x)
		{
			commandPosition.x = x * commandPosition.w + cardPosition.x;
			commandPosition.y = y * commandPosition.h + cardPosition.y;

			if (commands[y][x])
			{
				SDL_RenderFillRect(_renderer, &commandPosition);
			}
			else
			{
				SDL_RenderDrawRect(_renderer, &commandPosition);
			}
		}
	}
}
