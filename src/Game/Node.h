#include <list>
#include <memory>

#include "glm/vec2.hpp"

class Node
{
	friend class Map;

public:
	Node(const int& _x, const int& _y);

private:
	void updateCosts(std::shared_ptr<Node> _parent, const int& _parentDistance, std::shared_ptr<Node> _target);

	bool walkable;
	glm::ivec2 pos;
	int fCost;
	int gCost;
	int hCost;
	std::list<std::shared_ptr<Node>> neighbours;
	std::shared_ptr<Node> parent;
};
