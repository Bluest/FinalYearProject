#include <memory>

#include "SDL.h"

class Map;

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	std::shared_ptr<Map> map;
};
