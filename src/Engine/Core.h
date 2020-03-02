#include <list>
#include <memory>

#include "SDL2/SDL.h"

class Entity;
class Input;

class Core
{
public:
	static std::shared_ptr<Core> init(const int& _winW, const int& _winH);
	~Core();

	std::shared_ptr<Entity> addEntity();
	std::shared_ptr<Input> getInput();

	void run();

private:
	void draw();

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::weak_ptr<Core> self;
	std::shared_ptr<Input> input;

	std::list<std::shared_ptr<Entity>> entities;
};
