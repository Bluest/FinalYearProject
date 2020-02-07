#include <list>
#include <memory>
#include <vector>

class Node;

class Map
{
public:
	Map();

	bool findPath();
	//std::list<std::shared_ptr<Node>> findPath(const std::shared_ptr<Node>& _start, const std::shared_ptr<Node>& _end);

private:
	const int width = 10;
	const int height = 10;

	std::vector<std::vector<std::shared_ptr<Node>>> nodes;

	// 2D vectors instead of lists?
	// Compare speed and memory
	std::list<std::shared_ptr<Node>> open;
	std::list<std::shared_ptr<Node>> closed;
};
