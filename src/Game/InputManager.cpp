#include "Command.h"
#include "Commandable.h"
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
									if (commands[y][x]->getType() == Command::Type::INSTANT)
									{
										if ((*it)->getComponent<Commandable>()->hasCommand(commands[y][x]))
										{
											commands[y][x]->action(*it, glm::vec2(), nullptr);
										}
									}
									else
									{
										// Change state
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
				std::shared_ptr<Entity> selected = gameManager->getEntityAt(input->mousePosition());
				if (selected)
				{
					selection.clear();
					selection.push_back(selected);
					commands = selected->getComponent<Commandable>()->getCommands();
				}
			}
		}

		if (input->mousePress(SDL_BUTTON_RIGHT))
		{
			// CommandManager::rightClick()

			glm::vec2 position = (glm::vec2(input->mousePosition().x, input->mousePosition().y) - nodeSize / 2) / nodeSize;
			std::shared_ptr<Entity> target = gameManager->getEntityAt(input->mousePosition());

			for (auto it = selection.begin(); it != selection.end(); ++it)
			{
				(*it)->getComponent<Commandable>()->getRightClickCommand()->action(*it, position, target);
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
