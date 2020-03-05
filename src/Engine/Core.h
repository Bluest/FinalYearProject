#include <list>
#include <memory>

#include "SDL2/SDL.h"

class Entity;
class Input;
class Time;

class Core
{
public:
	static std::shared_ptr<Core> init(const int& _winW, const int& _winH, const float& _fpsCap);
	~Core();

	std::shared_ptr<Entity> addEntity();
	void run();

	float getDeltaTime();
	std::shared_ptr<Input> getInput();

private:
	void draw();

	SDL_Window* window;
	SDL_Renderer* renderer;

	std::weak_ptr<Core> self;
	std::shared_ptr<Input> input;
	std::unique_ptr<Time> time;

	std::list<std::shared_ptr<Entity>> entities;
};
