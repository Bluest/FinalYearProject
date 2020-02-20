#include <list>
#include <memory>

#include "SDL2/SDL.h"

class Input;
class Map;
class Object;

class Game
{
public:
	Game();
	~Game();

	void run();
	void addObject(std::shared_ptr<Object> _object);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;

	std::shared_ptr<Input> input;
	std::shared_ptr<Map> map;
	std::list<std::shared_ptr<Object>> objects;
};
