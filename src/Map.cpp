#include <fstream>
#include <iostream>
#include <string>

#include "Map.h"
#include "Node.h"

Map::Map()
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

void Map::loadTerrain()
{
	std::ifstream file("map.txt");
	std::string line;
	char cell;

	for (int y = 0; y < height; ++y)
	{
		std::getline(file, line);
		for (size_t x = 0; x < line.size(); ++x)
		{
			cell = line[x];
			nodes[y][x]->isTerrain = atoi(&cell);
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

void Map::drawNodeGrid(SDL_Renderer* _renderer)
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

	// Draw open nodes
	for (auto it = open.begin(); it != open.end(); ++it)
	{
		nodePos = { nodeSize * (*it)->x, nodeSize * (*it)->y, nodeSize + 1, nodeSize + 1 };
		SDL_SetRenderDrawColor(_renderer, 192, 192, 255, 255);
		SDL_RenderFillRect(_renderer, &nodePos);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(_renderer, &nodePos);
	}

	// Draw closed nodes
	for (auto it = closed.begin(); it != closed.end(); ++it)
	{
		nodePos = { nodeSize * (*it)->x, nodeSize * (*it)->y, nodeSize + 1, nodeSize + 1 };
		SDL_SetRenderDrawColor(_renderer, 128, 128, 255, 255);
		SDL_RenderFillRect(_renderer, &nodePos);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(_renderer, &nodePos);
	}

	// Draw path
	for (auto it = path.begin(); it != path.end(); ++it)
	{
		nodePos = { nodeSize * (*it)->x, nodeSize * (*it)->y, nodeSize + 1, nodeSize + 1 };
		SDL_SetRenderDrawColor(_renderer, 255, 255, 0, 255);
		SDL_RenderFillRect(_renderer, &nodePos);
		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(_renderer, &nodePos);
	}
}

std::list<std::shared_ptr<Node>> Map::findPath(const int& _startX, const int& _startY, const int& _targetX, const int& _targetY)
{
	open.clear();
	closed.clear();
	path.clear();

	std::shared_ptr<Node> start = nodes[_startY / nodeSize][_startX / nodeSize];
	std::shared_ptr<Node> target = nodes[_targetY / nodeSize][_targetX / nodeSize];

	if (start == target)
	{
		path.push_back(target);
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

			if (current->gCost + 1 < (*it)->gCost)
			{
				std::cout << "Path updated at [" << (*it)->x << ", " << (*it)->y << "]: " << (*it)->gCost << " -> " << current->gCost << std::endl;
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
			std::cout << "No path!" << std::endl;
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
			// TODO: Move to farthest visible node

			while (current != start)
			{
				path.push_front(current);
				current = current->parent;
			}
			path.push_front(start);

			return path;
		}
	}
}
