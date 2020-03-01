#include "Core.h"
#include "Entity.h"
#include "Input.h"

std::shared_ptr<Core> Core::init(const int& _winW, const int& _winH)
{
	std::shared_ptr<Core> core = std::make_shared<Core>();
	core->self = core;
	core->input = std::make_shared<Input>();

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(_winW, _winH, 0, &core->window, &core->renderer);

	return core;
}

Core::~Core()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr<Entity> entity = std::make_shared<Entity>();
	entity->self = entity;
	entity->core = self;
	entities.push_back(entity);

	return entity;
}

std::shared_ptr<Input> Core::getInput()
{
	return input;
}

void Core::run()
{
	while (input->processInput())
	{
		for (auto it = entities.begin(); it != entities.end(); ++it)
		{
			(*it)->update();
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		for (auto it = entities.begin(); it != entities.end(); ++it)
		{
			(*it)->draw();
		}

		SDL_RenderPresent(renderer);
	}
}
