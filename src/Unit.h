#include <list>
#include <memory>

#include "SDL2/SDL.h"

class Node;

struct vec2f
{
	float x;
	float y;
};

class Unit
{
public:
	Unit(const float& _size, const float& _speed, const float& _posX, const float& _posY);

	bool isClicked(const int& _clickX, const int& _clickY);
	void move(const std::list<std::shared_ptr<Node>>& _path);
	void stop();
	void update();
	void draw(SDL_Renderer* _renderer);

	vec2f getPos();

private:
	void moveToPathIt();

	// Stats
	float size;
	float speed;

	// State
	// TODO: Navigation Class
	vec2f pos;
	vec2f dest;
	vec2f step;
	std::list<std::shared_ptr<Node>> path; // TODO: list of vec2 instead of nodes
	std::list<std::shared_ptr<Node>>::iterator pathIt;
	bool updatePathIt;
};
