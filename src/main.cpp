#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "Game.h"

struct Node
{
	Node(const int& _x, const int& _y) : x(_x), y(_y) {}

	bool isTerrain = false;
	int x;
	int y;
    int fCost = 0;
    int gCost = 0;
    int hCost = 0;
    std::shared_ptr<Node> parent = nullptr;
};

std::vector<std::vector<std::shared_ptr<Node>>> initMap(const int& _mapW, const int& _mapH)
{
	std::vector<std::vector<std::shared_ptr<Node>>> map;

	map.resize(_mapH);

	for (int y = 0; y < _mapH; ++y)
	{
		for (int x = 0; x < _mapW; ++x)
		{
			map[y].emplace_back(std::make_shared<Node>(x, y));
		}
	}

	int wallX = _mapW * 3 / 4;
	int wallStartY = _mapH / 5;

	for (int y = wallStartY; y < _mapH - wallStartY; ++y)
	{
		map[y][wallX]->isTerrain = true;
	}

	return map;
}

int main(int argc, char* argv[])
{
	const int mapW = 10;
	const int mapH = 10;
	const int nodeSize = 50;
	SDL_Rect tilePos;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event = { NULL };

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(mapW * nodeSize, mapH * nodeSize, 0, &window, &renderer);

	std::vector<std::vector<std::shared_ptr<Node>>> map = initMap(mapW, mapH);

	// 2D vectors instead of lists?
	std::list<std::shared_ptr<Node>> open;
	std::list<std::shared_ptr<Node>> closed;

	std::shared_ptr<Node> start = map[4][2];
	std::shared_ptr<Node> end = map[4][8];
	open.push_back(start);

	std::shared_ptr<Node> current = start;

	for (int i = 0; i < 1000; ++i)
	{
		open.push_back(map[rand() % mapH][rand() % mapW]);

		std::cout << "# " << i << std::endl;
		if (!open.empty())
		{
			current = open.front();
			std::cout << "current = " << current->x << ", " << current->y << std::endl;
		}
		else std::cout << "open is empty!" << std::endl;

		for (auto it = open.begin(); it != open.end(); ++it)
		{
			if ((*it)->fCost < current->fCost)
			{
				current = *it;
				std::cout << "current = " << current->x << ", " << current->y << std::endl;
			}
		}
		open.remove(current);
		closed.push_back(current);

		if (current == end)
		{
			std::cout << "Path found!";
			break;
		}

		/*
		foreach neighbour of the current node
			if neighbour is is closed
				skip to next neighbour

			if new path to neighbour is shorter OR neighbour is not in open
				set fCost of neighbour
				set parent of neighbour to current
				if neighbour is not in open
					add neighbour to open
		*/

		SDL_WaitEvent(&event);
		if (event.type == SDL_QUIT)
		{
			break;
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		for (int y = 0; y < mapH; ++y)
		{
			for (int x = 0; x < mapW; ++x)
			{
				SDL_Rect tilePos = { nodeSize * x, nodeSize * y, nodeSize + 1, nodeSize + 1 };

				if (map[y][x]->isTerrain)
				{
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(renderer, &tilePos);
				}
				else
				{
					SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
					SDL_RenderDrawRect(renderer, &tilePos);
				}
			}
		}

		for (auto it = open.begin(); it != open.end(); ++it)
		{
			tilePos = { nodeSize * (*it)->x, nodeSize * (*it)->y, nodeSize + 1, nodeSize + 1 };
			SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
			SDL_RenderFillRect(renderer, &tilePos);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &tilePos);
		}

		for (auto it = closed.begin(); it != closed.end(); ++it)
		{
			tilePos = { nodeSize * (*it)->x, nodeSize * (*it)->y, nodeSize + 1, nodeSize + 1 };
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer, &tilePos);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &tilePos);
		}

		tilePos = { nodeSize * start->x, nodeSize * start->y, nodeSize + 1, nodeSize + 1 };
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer, &tilePos);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &tilePos);

		tilePos = { nodeSize * end->x, nodeSize * end->y, nodeSize + 1, nodeSize + 1 };
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &tilePos);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &tilePos);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	//Game game;
	//game.run();

	return 0;
}
