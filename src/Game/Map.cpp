#include <fstream>
#include <string>

#include "Map.h"
#include "Node.h"

void Map::onStart()
{
	nodes.resize(width);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			nodes[y].emplace_back(std::make_shared<Node>(x, y));
		}
	}

	// Set neighbours
	const int neighbourX[4] = { 0, 1, 0, -1 };
	const int neighbourY[4] = { -1, 0, 1, 0 };

	// For each node...
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			// For each neighbour...
			for (int i = 0; i < 4; ++i)
			{
				// If this neighbour is not out of bounds...
				if (x + neighbourX[i] >= 0 && x + neighbourX[i] < width &&
					y + neighbourY[i] >= 0 && y + neighbourY[i] < height)
				{
					nodes[y][x]->neighbours.push_back(nodes[y + neighbourY[i]][x + neighbourX[i]]);
				}
			}
		}
	}

	loadTerrain();
}

void Map::onDraw(SDL_Renderer* _renderer)
{
	SDL_Rect nodePos;

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			nodePos = { nodeSize * x, nodeSize * y, nodeSize + 1, nodeSize + 1 };

			if (nodes[y][x]->isTerrain)
			{
				SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(_renderer, &nodePos);
			}
			else
			{
				SDL_SetRenderDrawColor(_renderer, 224, 224, 224, 255);
				SDL_RenderDrawRect(_renderer, &nodePos);
			}
		}
	}
}

std::list<glm::vec2> Map::findPath(const glm::vec2& _start, const glm::vec2& _target)
{
	refreshNodes();

	// 2D vectors instead of lists?
	// Compare speed and memory
	std::list<std::shared_ptr<Node>> open;
	std::list<std::shared_ptr<Node>> closed;
	std::list<glm::vec2> path;

	// Round positions to nearest int
	std::shared_ptr<Node> start = nodes[int(_start.y + 0.5f)][int(_start.x + 0.5f)];
	std::shared_ptr<Node> target = nodes[int(_target.y + 0.5f)][int(_target.x + 0.5f)];

	if (start == target)
	{
		path.push_back(target->pos);
		return path;
	}

	if (target->isTerrain)
	{
		return path;
	}

	std::shared_ptr<Node> current = start;
	closed.push_back(start);

	for (;;)
	{
		for (auto it = current->neighbours.begin(); it != current->neighbours.end(); ++it)
		{
			// If neighbour is terrain or is in closed, continue to next neighbour
			if ((*it)->isTerrain || std::find(closed.begin(), closed.end(), *it) != closed.end())
			{
				continue;
			}

			// If this path is shorter or neighbour is not in open...
			if (current->gCost + 1 < (*it)->gCost || std::find(open.begin(), open.end(), *it) == open.end())
			{
				(*it)->updateCosts(current, target);

				// If neighbour is not in open, add it
				if (std::find(open.begin(), open.end(), *it) == open.end())
				{
					open.push_back(*it);
				}
			}
		}

		if (!open.empty())
		{
			current = open.front();
		}
		else
		{
			return path;
		}

		for (auto it = open.begin(); it != open.end(); ++it)
		{
			if ((*it)->fCost < current->fCost)
			{
				current = *it;
			}
		}

		open.remove(current);
		closed.push_back(current);

		if (current == target)
		{
			while (current != start)
			{
				path.push_front(current->pos);
				current = current->parent;
			}

			return path;
		}
	}
}

void Map::loadTerrain()
{
	std::ifstream file("map.txt");
	std::string line;

	for (int y = 0; y < height; ++y)
	{
		std::getline(file, line);
		for (size_t x = 0; x < line.size(); ++x)
		{
			if (line[x] == '#')
			{
				nodes[y][x]->isTerrain = true;
			}
		}
	}
}

void Map::refreshNodes()
{
	// Only refresh nodes in the open and closed lists?
	// ie. The ones that were set to non-zero values

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			nodes[y][x]->gCost = 0;
		}
	}
}