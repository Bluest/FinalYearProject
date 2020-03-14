#include "Node.h"

Node::Node(const int& _x, const int& _y)
{
	pos.x = _x;
	pos.y = _y;

	walkable = true;
	fCost = 0;
	gCost = 0;
	hCost = 0;
	parent = nullptr;
}

void Node::updateCosts(std::shared_ptr<Node> _parent, const int& _parentDistance, std::shared_ptr<Node> _target)
{
	parent = _parent;

	gCost = parent->gCost + _parentDistance;

	glm::vec2 delta = glm::vec2(_target->pos - pos);
	hCost = 10 * int(hypotf(delta.x, delta.y));
	//hCost = 10 * glm::length(delta);

	fCost = gCost + hCost;
}
