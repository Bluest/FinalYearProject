#include "Command.h"
#include "GameManager.h"
#include "InputManager.h"
#include "Selectable.h"

void InputManager::setGameManager(const std::shared_ptr<GameManager>& _gameManager)
{
	gameManager = _gameManager;
}

void InputManager::onStart()
{
	input = getCore()->getInput();

	state = State::SELECT;

	// UI
	panelPosition.x = 350;
	panelPosition.y = 500;
	panelPosition.w = 150;
	panelPosition.h = 100;

	commandPosition.w = 50;
	commandPosition.h = 50;
}

void InputManager::onUpdate()
{
	switch (state)
	{
	case State::SELECT:
	{
		if (input->mousePress(SDL_BUTTON_LEFT))
		{
			SDL_Point clickPosition = input->mousePosition();

			// Clicked UI?
			if (SDL_PointInRect(&clickPosition, &panelPosition))
			{
				// UIManager

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
								for (auto it = selection.begin(); it != selection.end(); ++it)
								{
									if ((*it)->hasCommand(commands[y][x]))
									{
										commands[y][x]->action(*it);
									}
								}
							}
						}
					}
				}
			}
			else // Clicked game area
			{
				// What did I click?

				// Single click, single unit
				std::list<std::shared_ptr<Selectable>> selectables = gameManager->getSelectables();
				for (auto it = selectables.begin(); it != selectables.end(); ++it)
				{
					// If an object is clicked, select it
					if ((*it)->isClicked(input->mousePosition()))
					{
						selection.clear();
						selection.push_back(*it);
						commands = (*it)->getCommands();
						break;
					}
				}
			}
		}

		if (input->mousePress(SDL_BUTTON_RIGHT))
		{
			printf("Current selection:\n");
			for (auto it = selection.begin(); it != selection.end(); ++it)
			{
				printf("%p\n", (*it).get());
			}
		}

		break;
	}
	case State::TARGET:
	{
		// LMB: Select target
		
		if (input->mousePress(SDL_BUTTON_RIGHT))
		{
			// Cancel out of target selection state
			state = State::SELECT;
			// break?
		}

		break;
	}
	case State::AIM:
	{
		// LMB: Select position

		if (input->mousePress(SDL_BUTTON_RIGHT))
		{
			// Cancel out of position selection state
			state = State::SELECT;
			// break?
		}

		break;
	}
	}
}

void InputManager::onDraw(SDL_Renderer* _renderer)
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
