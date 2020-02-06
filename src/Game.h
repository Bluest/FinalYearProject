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
	const int winW = 640;
	const int winH = 480;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	std::shared_ptr<Map> map;
};
