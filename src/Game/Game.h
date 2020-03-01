#include <memory>

#include "SDL2/SDL.h"

class GameState;
class Map;
class Player;

class Game
{
public:
	Game();
	~Game();

	void run();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

	std::shared_ptr<Map> map;
	std::shared_ptr<GameState> gameState;
	std::shared_ptr<Player> player;
};
