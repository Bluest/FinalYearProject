#include <list>
#include <memory>
#include <vector>

class Node;

class Map
{
public:
	Map();

private:
	const int mapW = 10;
	const int mapH = 10;
	const int nodeSize = 50;

	std::vector<std::vector<std::shared_ptr<Node>>> nodes;

	// 2D vectors instead of lists?
	// Compare speed and memory
	std::list<std::shared_ptr<Node>> open;
	std::list<std::shared_ptr<Node>> closed;
};
