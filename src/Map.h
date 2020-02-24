#include <list>
#include <memory>
#include <vector>

#include "glm/vec2.hpp"
#include "SDL2/SDL_render.h"

class Node;

class Map
{
public:
	Map();

	void refreshNodes();
	void drawNodeGrid(SDL_Renderer* _renderer);
	std::list<glm::vec2> findPath(const glm::ivec2& _start, const glm::ivec2& _target);

private:
	void loadTerrain();

	const int width = 10;
	const int height = 10;
	const int nodeSize = 50;

	std::vector<std::vector<std::shared_ptr<Node>>> nodes;
};
