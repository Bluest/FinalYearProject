#include <list>

#include "glm/vec2.hpp"

#include "Faction.h"
#include "Game.h"
#include "Input.h"
#include "Map.h"
#include "Match.h"
#include "Unit.h"

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(500, 500, 0, &window, &renderer);

	event = { 0u };
	input = std::make_shared<Input>();
	map = std::make_shared<Map>();
	match = std::make_shared<Match>(/*map*/);
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::run()
{
	Faction player;
	Faction enemy;

	player.createUnit(20.0f, 1.0f, glm::vec2(75.0f, 475.0f));
	player.createUnit(20.0f, 1.0f, glm::vec2(25.0f, 475.0f));
	player.createUnit(20.0f, 1.0f, glm::vec2(25.0f, 425.0f));

	// TODO: Player Class
	// units, resources, structures, etc.
	std::list<std::shared_ptr<Unit>> units;
	units.emplace_back(std::make_shared<Unit>(20.0f, 5.0f, glm::vec2(75.0f, 475.0f)));
	units.emplace_back(std::make_shared<Unit>(20.0f, 5.0f, glm::vec2(25.0f, 475.0f)));
	units.emplace_back(std::make_shared<Unit>(20.0f, 5.0f, glm::vec2(25.0f, 425.0f)));
	// world space should definitely be { 3.0f, 9.0f } instead of { 75.0f, 475.0f } later

	std::list<std::shared_ptr<Unit>> selection;

	// Temporary: Start with everything selected
	for (auto it = units.begin(); it != units.end(); ++it)
	{
		selection.push_back(*it);
	}

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
					glm::ivec2 click;
					SDL_GetMouseState(&click.x, &click.y);

					selection.clear();
					for (auto it = units.begin(); it != units.end(); ++it)
					{
						// If a unit is clicked, select it and break
						if ((*it)->isClicked(click))
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
					glm::ivec2 target;
					SDL_GetMouseState(&target.x, &target.y);

					for (auto it = selection.begin(); it != selection.end(); ++it)
					{
						// TODO?: (*it)->move(target)
						(*it)->move(map->findPath((*it)->getPosition(), target));
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
