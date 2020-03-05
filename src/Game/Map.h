#include <vector>

#include "Engine.h"

class Node;

class Map : public Component
{
public:
	std::list<glm::vec2> findPath(const glm::vec2& _start, const glm::vec2& _target);

private:
	void onStart();
	void onDraw(SDL_Renderer* _renderer);

	void loadTerrain();
	void refreshNodes();

	const int width = 20;
	const int height = 20;
	const int nodeSize = 25;

	std::vector<std::vector<std::shared_ptr<Node>>> nodes;
};
