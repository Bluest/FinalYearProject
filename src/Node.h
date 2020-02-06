#include <list>
#include <memory>

class Node
{
public:
	Node(const int& _x, const int& _y) : x(_x), y(_y) {}

	void updateCosts(std::shared_ptr<Node> _parent, std::shared_ptr<Node> _target)
	{
		parent = _parent;
		gCost = parent->gCost + 1;
		hCost = abs(_target->x - x) + abs(_target->y - y);
		fCost = gCost + hCost;
	}

	bool isTerrain = false;
	int x;
	int y;
	int fCost = 0;
	int gCost = 0;
	int hCost = 0;
	std::list<std::shared_ptr<Node>> neighbours;
	std::shared_ptr<Node> parent = nullptr;
};
