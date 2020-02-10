#include <list>
#include <memory>
#include <vector>

#include "SDL2/SDL.h"

class Node;

class Map
{
public:
	Map();

	void loadTerrain();
	void refreshNodes();
	void drawNodeGrid(SDL_Renderer* _renderer);
	std::list<std::shared_ptr<Node>> findPath(const int& _startX, const int& _startY, const int& _targetX, const int& _targetY);
	//std::list<std::shared_ptr<Node>> findPath(const vec2i& _start, const vec2i& _target);

private:
	const int width = 10;
	const int height = 10;
	const int nodeSize = 50;

	std::vector<std::vector<std::shared_ptr<Node>>> nodes;

	// 2D vectors instead of lists?
	// Compare speed and memory
	std::list<std::shared_ptr<Node>> open;
	std::list<std::shared_ptr<Node>> closed;
	std::list<std::shared_ptr<Node>> path; // Currently only stored for drawing purposes
};
