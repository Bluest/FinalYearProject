#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "Game.h"

struct Node
{
	Node(const int& _x, const int& _y) : x(_x), y(_y) {}

	void updateCosts(std::shared_ptr<Node> _parent, std::shared_ptr<Node> _target)
	{
		parent = _parent;

		gCost = parent->gCost + 1;
		hCost = abs(_target->x - x) + abs(_target->y - y);

		fCost = gCost + hCost;
	}

	bool isTerrain = false;
	int x;
	int y;
	int fCost = 0;
	int gCost = 0;
	int hCost = 0;
	std::list<std::shared_ptr<Node>> neighbours;
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

	const int neighbourX[4] = { 0, 1, 0, -1 };
	const int neighbourY[4] = { -1, 0, 1, 0 };

	// For each node...
	for (int y = 0; y < _mapH; ++y)
	{
		for (int x = 0; x < _mapW; ++x)
		{
			// For each neighbour...
			for (int i = 0; i < 4; ++i)
			{
				// If this neighbour is not out of bounds...
				if (x + neighbourX[i] >= 0 && x + neighbourX[i] < _mapW &&
					y + neighbourY[i] >= 0 && y + neighbourY[i] < _mapH)
				{
					map[y][x]->neighbours.push_back(map[y + neighbourY[i]][x + neighbourX[i]]);
				}
			}
		}
	}

	// Terrain
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
	SDL_Rect nodePos;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event = { NULL };

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(mapW * nodeSize, mapH * nodeSize, 0, &window, &renderer);

	std::vector<std::vector<std::shared_ptr<Node>>> map = initMap(mapW, mapH);

	std::list<std::shared_ptr<Node>> open;
	std::list<std::shared_ptr<Node>> closed;

	std::shared_ptr<Node> start = map[4][2];
	std::shared_ptr<Node> end = map[4][8];

	std::shared_ptr<Node> current = start;
	closed.push_back(start);

	int i = 0;
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
				std::cout << "Old path to [" << (*it)->x << ", " << (*it)->y << "]: " << (*it)->gCost << std::endl;
				std::cout << "New path to [" << (*it)->x << ", " << (*it)->y << "]: " << current->gCost + 1 << std::endl;
			}

			// If this path is shorter or neighbour is not in open...
			if (current->gCost + 1 < (*it)->gCost || std::find(open.begin(), open.end(), *it) == open.end())
			{
				++i;

				(*it)->updateCosts(current, end);

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
			break;
		}

		for (auto it = open.begin(); it != open.end(); ++it)
		{
			if ((*it)->fCost < current->fCost)
			{
				current = *it;
			}
		}

		std::cout << i << ": Checking [" << current->x << ", " << current->y << "] (fCost = " << current->fCost << ": gCost = " << current->gCost << ", hCost = " << current->hCost << ")" << std::endl;

		open.remove(current);
		closed.push_back(current);

		if (current == end)
		{
			std::cout << "Path found! " << i << " checks" << std::endl;
			break;
		}
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	for (int y = 0; y < mapH; ++y)
	{
		for (int x = 0; x < mapW; ++x)
		{
			SDL_Rect nodePos = { nodeSize * x, nodeSize * y, nodeSize + 1, nodeSize + 1 };

			if (map[y][x]->isTerrain)
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderFillRect(renderer, &nodePos);
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderDrawRect(renderer, &nodePos);
			}
		}
	}

	// Draw open nodes
	for (auto it = open.begin(); it != open.end(); ++it)
	{
		nodePos = { nodeSize * (*it)->x, nodeSize * (*it)->y, nodeSize + 1, nodeSize + 1 };
		SDL_SetRenderDrawColor(renderer, 192, 192, 255, 255);
		SDL_RenderFillRect(renderer, &nodePos);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &nodePos);
	}

	// Draw closed nodes
	for (auto it = closed.begin(); it != closed.end(); ++it)
	{
		nodePos = { nodeSize * (*it)->x, nodeSize * (*it)->y, nodeSize + 1, nodeSize + 1 };
		SDL_SetRenderDrawColor(renderer, 128, 128, 255, 255);
		SDL_RenderFillRect(renderer, &nodePos);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &nodePos);
	}

	// Draw start node
	nodePos = { nodeSize * start->x, nodeSize * start->y, nodeSize + 1, nodeSize + 1 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &nodePos);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &nodePos);

	// Draw end node
	nodePos = { nodeSize * end->x, nodeSize * end->y, nodeSize + 1, nodeSize + 1 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &nodePos);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &nodePos);

	// Draw parent links
	for (int y = 0; y < mapH; ++y)
	{
		for (int x = 0; x < mapW; ++x)
		{
			if (map[y][x]->parent)
			{
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderDrawLine(renderer,
					nodeSize * map[y][x]->x + nodeSize / 2,
					nodeSize * map[y][x]->y + nodeSize / 2,
					nodeSize * map[y][x]->parent->x + nodeSize / 2,
					nodeSize * map[y][x]->parent->y + nodeSize / 2);
			}
		}
	}

	if (current == end)
	{
		current = current->parent;
		while (current != start)
		{
			nodePos = { nodeSize * current->x, nodeSize * current->y, nodeSize + 1, nodeSize + 1 };
			SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
			SDL_RenderFillRect(renderer, &nodePos);
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderDrawRect(renderer, &nodePos);

			current = current->parent;
		}
	}

	SDL_RenderPresent(renderer);

	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	//Game game;
	//game.run();

	return 0;
}
