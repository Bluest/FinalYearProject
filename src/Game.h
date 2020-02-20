#include <memory>

#include "SDL2/SDL.h"

class Input;
class Map;
class Match;

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

	std::shared_ptr<Input> input;
	std::shared_ptr<Map> map;
	std::shared_ptr<Match> match;
};
