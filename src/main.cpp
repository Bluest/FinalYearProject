#include <iostream>
#include <list>
#include <memory>
#include <vector>

#include "Game.h"

int main(int argc, char* argv[])
{
	/*const int nodeSize = 50;
	SDL_Rect nodePos;

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
	}*/

	Game game;
	game.run();

	return 0;
}
