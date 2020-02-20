#include <list>
#include <memory>

#include "glm/vec2.hpp"
#include "SDL2/SDL_render.h"

class Unit
{
public:
	Unit(const float& _size, const float& _speed, const glm::vec2& _position);

	bool isClicked(const glm::ivec2& _click);
	void move(const std::list<glm::vec2>& _path);
	void stop();
	void update();
	void draw(SDL_Renderer* _renderer);

	glm::vec2 getPosition();

private:
	void moveToPathIt();

	// Stats
	float size;
	float speed;

	// State
	// TODO: Navigation Class
	glm::vec2 position;
	glm::vec2 dest;
	glm::vec2 step;
	std::list<glm::vec2> path;
	std::list<glm::vec2>::iterator pathIt;
	bool updatePathIt;
};
