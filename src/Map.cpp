#include "Map.h"
#include "Node.h"

Map::Map()
{
	nodes.resize(mapW);

	for (int y = 0; y < mapH; ++y)
	{
		for (int x = 0; x < mapW; ++x)
		{
			nodes[y].emplace_back(std::make_shared<Node>(x, y));
		}
	}

	const int neighbourX[4] = { 0, 1, 0, -1 };
	const int neighbourY[4] = { -1, 0, 1, 0 };

	// For each node...
	for (int y = 0; y < mapH; ++y)
	{
		for (int x = 0; x < mapW; ++x)
		{
			// For each neighbour...
			for (int i = 0; i < 4; ++i)
			{
				// If this neighbour is not out of bounds...
				if (x + neighbourX[i] >= 0 && x + neighbourX[i] < mapW &&
					y + neighbourY[i] >= 0 && y + neighbourY[i] < mapH)
				{
					nodes[y][x]->neighbours.push_back(nodes[y + neighbourY[i]][x + neighbourX[i]]);
				}
			}
		}
	}

	// Terrain
	// TODO: Replace with read from file
	int wallX = mapW * 3 / 4;
	int wallStartY = mapH / 5;

	for (int y = wallStartY; y < mapH - wallStartY; ++y)
	{
		nodes[y][wallX]->isTerrain = true;
	}
}
