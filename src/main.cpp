#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "Game.h"

struct Node
{
	bool isTerrain = false;
    int fCost = 0;
    int gCost = 0;
    int hCost = 0;
    std::shared_ptr<Node> parent = nullptr;
};

std::vector<std::vector<std::shared_ptr<Node>>> initMap()
{
	std::vector<std::vector<std::shared_ptr<Node>>> map;

	int width = 20;
	int height = 10;

	map.resize(height);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			map[y].emplace_back(std::make_shared<Node>());
		}
	}

	int wallX = 15;
	int wallY = 2;

	for (; wallY < 8; ++wallY)
	{
		map[wallY][wallX]->isTerrain = true;
	}

	return map;
}

int main(int argc, char* argv[])
{
	std::vector<std::vector<std::shared_ptr<Node>>> map = initMap();

	std::list<std::shared_ptr<Node>> open;
	std::list<std::shared_ptr<Node>> closed;

	open.push_back(map[4][2]);

	/*
	add start node to open

	loop
		current = node in OPEN with the lowest fCost
		remove current from open
		add current to closed

		if current is the end node
			return

		foreach neighbour of the current node
			if neighbour is is closed
				skip to next neighbour

			if new path to neighbour is shorter OR neighbour is not in open
				set fCost of neighbour
				set parent of neighbour to current
				if neighbour is not in open
					add neighbour to open

		print
	*/

	for (size_t y = 0; y < map.size(); ++y)
	{
		for (size_t x = 0; x < map[y].size(); ++x)
		{
			if (map[y][x]->isTerrain)
			{
				std::cout << "#";
			}
			else
			{
				std::cout << "-";
			}
		}

		std::cout << std::endl;
	}

	//Game game;
	//game.run();

	return 0;
}
