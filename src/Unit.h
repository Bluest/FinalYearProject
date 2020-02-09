#include <list>
#include <memory>

#include "SDL.h"

class Node;

struct vec2f
{
	float x;
	float y;
};

class Unit
{
public:
	Unit(float _size, float _speed, float _posX, float _posY);
	
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

	// State (Should pathfinding logic be a separate class?)
	vec2f pos;
	vec2f dest;
	vec2f step;
	std::list<std::shared_ptr<Node>> path; // list of positions instead of nodes?
	std::list<std::shared_ptr<Node>>::iterator pathIt;
	bool updatePathIt;
};
