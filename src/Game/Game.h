#include "Engine.h"

class GameState;
class Map;
class Player;

class Game
{
public:
	Game();

	void start();

private:
	std::shared_ptr<Core> core;

	std::shared_ptr<Map> map;
	std::shared_ptr<GameState> gameState;
	std::shared_ptr<Player> player;
};
