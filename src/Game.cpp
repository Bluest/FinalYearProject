#include <memory>

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
	std::shared_ptr<Unit> unit = std::make_shared<Unit>(20.0f, 5.0f, 125.0f, 225.0f);

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
				case SDL_BUTTON_LEFT: unit->stop(); break;
				case SDL_BUTTON_RIGHT:
				{
					int targetX, targetY;
					SDL_GetMouseState(&targetX, &targetY);
					unit->move(map->findPath(int(unit->getPos().x), int(unit->getPos().y), targetX, targetY));
					break;
				}
				}
				break;
			}
			case SDL_QUIT: { quit = true; break; }
			}
		}

		// Update
		unit->update();

		// Draw
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		map->drawNodeGrid(renderer);
		unit->draw(renderer);
		SDL_RenderPresent(renderer);

		// Time
		SDL_Delay(16);
	}
}
