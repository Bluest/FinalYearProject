#include <memory>

#include "Game.h"
#include "Map.h"
#include "Unit.h"

Game::Game()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

	event = { 0U };
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
	std::shared_ptr<Unit> unit = std::make_shared<Unit>(25.0f, 5.0f, 320.0f, 240.0f);

	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT: unit->stop(); break;
				case SDL_BUTTON_RIGHT: unit->move(); map->findPath(); break;
				}
				break;
			}
			case SDL_QUIT: { quit = true; break; }
			}
		}

		unit->update();

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		unit->draw(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
}
