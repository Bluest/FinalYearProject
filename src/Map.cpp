#include <iostream>

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

	// Terrain
	// TODO: Replace with read from file
	int wallX = width * 3 / 4;
	int wallStartY = height / 5;

	for (int y = wallStartY; y < height - wallStartY; ++y)
	{
		nodes[y][wallX]->isTerrain = true;
	}
}

bool Map::findPath()
{
	// Identify which node the unit is currently in
	// Identify which node was clicked

	open.clear();
	closed.clear();

	std::shared_ptr<Node> _start = nodes[4][2];
	std::shared_ptr<Node> _target = nodes[4][8];

	std::shared_ptr<Node> current = _start;
	closed.push_back(_start);

	bool quit = false;
	while (!quit)
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
				std::cout << "Path updated at [" << (*it)->x << ", " << (*it)->y << "]: " << std::endl;
			}

			// If this path is shorter or neighbour is not in open...
			if (current->gCost + 1 < (*it)->gCost || std::find(open.begin(), open.end(), *it) == open.end())
			{
				(*it)->updateCosts(current, _target);

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
			return false;
		}

		for (auto it = open.begin(); it != open.end(); ++it)
		{
			if ((*it)->fCost < current->fCost)
			{
				current = *it;
			}
		}

		//std::cout << "Checking [" << current->x << ", " << current->y << "] (fCost = " << current->fCost << ": gCost = " << current->gCost << ", hCost = " << current->hCost << ")" << std::endl;

		open.remove(current);
		closed.push_back(current);

		if (current == _target)
		{
			std::cout << "Path found!" << std::endl;
			return true;
		}
	}
}
