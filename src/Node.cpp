#include "Node.h"

Node::Node(const int& _x, const int& _y)
{
	pos.x = _x;
	pos.y = _y;

	isTerrain = false;
	fCost = 0;
	gCost = 0;
	hCost = 0;
	parent = nullptr;
}

void Node::updateCosts(std::shared_ptr<Node> _parent, std::shared_ptr<Node> _target)
{
	parent = _parent;
	gCost = parent->gCost + 1;
	hCost = abs(_target->pos.x - pos.x) + abs(_target->pos.y - pos.y);
	fCost = gCost + hCost;
}
