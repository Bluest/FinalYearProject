#include "Engine.h"

class Game
{
public:
	Game();

	void start();

private:
	std::shared_ptr<Core> core;
};
