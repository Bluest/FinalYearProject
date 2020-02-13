#include <list>

#include "Game.h"
#include "Map.h"
#include "Unit.h"

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(500, 500, 0, &window, &renderer);

	event = { 0u };
	map = std::make_shared<Map>();
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	// TODO: Player Class
	// units, resources, structures, etc.
	std::list<std::shared_ptr<Unit>> units;
	units.emplace_back(std::make_shared<Unit>(20.0f, 5.0f, 75.0f, 475.0f));
	units.emplace_back(std::make_shared<Unit>(20.0f, 5.0f, 25.0f, 475.0f));
	units.emplace_back(std::make_shared<Unit>(20.0f, 5.0f, 25.0f, 425.0f));

	std::list<std::shared_ptr<Unit>> selection;

	bool quit = false;
	while (!quit)
	{
		// Input
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					int clickX, clickY;
					SDL_GetMouseState(&clickX, &clickY);

					selection.clear();
					for (auto it = units.begin(); it != units.end(); ++it)
					{
						// If a unit is , select it and break
						if ((*it)->isClicked(clickX, clickY))
						{
							selection.push_back(*it);
							break;
						}
					}

					if (!selection.empty()) printf("Selected %p\n", selection.front().get()); else printf("No selection\n");
					break;
				}
				case SDL_BUTTON_RIGHT:
				{
					// TODO: Input Class
					int targetX, targetY;
					SDL_GetMouseState(&targetX, &targetY);

					for (auto it = selection.begin(); it != selection.end(); ++it)
					{
						// TODO?: (*it)->move(targetX, targetY)
						(*it)->move(map->findPath(int((*it)->getPos().x), int((*it)->getPos().y), targetX, targetY));
					}
					break;
				}
				case SDL_BUTTON_MIDDLE:
				{
					for (auto it = units.begin(); it != units.end(); ++it)
					{
						(*it)->stop();
					}
					break;
				}
				}
				break;
			}
			case SDL_QUIT: { quit = true; break; }
			}
		}

		// Update
		map->refreshNodes();

		for (auto it = units.begin(); it != units.end(); ++it)
		{
			(*it)->update();
		}

		// Draw
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		map->drawNodeGrid(renderer);

		for (auto it = units.begin(); it != units.end(); ++it)
		{
			(*it)->draw(renderer);
		}

		SDL_RenderPresent(renderer);

		// TODO: Time Class
		SDL_Delay(16);
	}
}
