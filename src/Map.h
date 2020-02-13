#include <list>
#include <memory>
#include <vector>

#include "glm/vec2.hpp"
#include "SDL2/SDL.h"

class Node;

class Map
{
public:
	Map();

	void loadTerrain();
	void refreshNodes();
	void drawNodeGrid(SDL_Renderer* _renderer);
	std::list<std::shared_ptr<Node>> findPath(const glm::ivec2& _start, const glm::ivec2& _target);

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
