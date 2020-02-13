#include <list>
#include <memory>

#include "glm/vec2.hpp"
#include "SDL2/SDL_render.h"

class Node;

class Unit
{
public:
	Unit(const float& _size, const float& _speed, const glm::vec2& _pos);

	bool isClicked(const glm::ivec2& _click);
	void move(const std::list<std::shared_ptr<Node>>& _path);
	void stop();
	void update();
	void draw(SDL_Renderer* _renderer);

	glm::vec2 getPos();

private:
	void moveToPathIt();

	// Stats
	float size;
	float speed;

	// State
	// TODO: Navigation Class
	glm::vec2 pos;
	glm::vec2 dest;
	glm::vec2 step;
	std::list<std::shared_ptr<Node>> path; // TODO: list of vec2 instead of nodes
	std::list<std::shared_ptr<Node>>::iterator pathIt;
	bool updatePathIt;
};
