#include <list>
#include <memory>

#include "glm/vec2.hpp"
#include "SDL2/SDL_render.h"

#include "SelectableObject.h"

class Unit : public SelectableObject
{
public:
	Unit(/*Type*/const float& _size, const float& _speed, const glm::vec2& _position);

	void move(const std::list<glm::vec2>& _path);
	void stop();
	void update();
	void draw(SDL_Renderer* _renderer);

protected:
	void moveToPathIt();

	// Stats
	float speed;

	// State
	// TODO: Navigation Class
	glm::vec2 dest;
	glm::vec2 step;
	std::list<glm::vec2> path;
	std::list<glm::vec2>::iterator pathIt;
	bool updatePathIt;
};
