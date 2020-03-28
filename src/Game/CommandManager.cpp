#include "Commandable.h"
#include "CommandCreateUnit.h"
#include "CommandManager.h"

void CommandManager::setSelection(const std::shared_ptr<std::list<std::shared_ptr<Entity>>>& _selection)
{
	selection = _selection;
}

void CommandManager::setCommands(const std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows>& _commands)
{
	commands = _commands;
}

void CommandManager::onStart()
{
	input = getCore()->getInput();

	panelPosition.x = 350;
	panelPosition.y = 500;
	panelPosition.w = 150;
	panelPosition.h = 100;

	commandPosition.w = 50;
	commandPosition.h = 50;
}

void CommandManager::onUpdate()
{
	// for each command
	// if (input->keyPress(hotkey))

	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		SDL_Point clickPosition = input->mousePosition();
		if (SDL_PointInRect(&clickPosition, &panelPosition))
		{
			for (size_t y = 0; y < commandSlotRows; ++y)
			{
				for (size_t x = 0; x < commandSlotColumns; ++x)
				{
					if (commands[y][x])
					{
						commandPosition.x = x * commandPosition.w + panelPosition.x;
						commandPosition.y = y * commandPosition.h + panelPosition.y;

						if (SDL_PointInRect(&clickPosition, &commandPosition))
						{
							for (auto it = selection->begin(); it != selection->end(); ++it)
							{
								if ((*it)->getComponent<Commandable>()->hasCommand(commands[y][x]))
								{
									commands[y][x]->action(*it);
								}
							}
						}
					}
				}
			}
		}
	}
}

void CommandManager::onDraw(SDL_Renderer* _renderer)
{
	SDL_SetRenderDrawColor(_renderer, 128, 128, 128, 255);
	SDL_RenderFillRect(_renderer, &panelPosition);

	SDL_SetRenderDrawColor(_renderer, 192, 192, 192, 255);
	for (size_t y = 0; y < commandSlotRows; ++y)
	{
		for (size_t x = 0; x < commandSlotColumns; ++x)
		{
			commandPosition.x = x * commandPosition.w + panelPosition.x;
			commandPosition.y = y * commandPosition.h + panelPosition.y;

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
