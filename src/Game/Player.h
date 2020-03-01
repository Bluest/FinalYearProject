#include <list>
#include <memory>

#include "SDL2/SDL_events.h"

class GameState;
class Input;
class SelectableObject;

class Player
{
public:
	Player(const std::shared_ptr<GameState>& _gameState);

	bool handleInput();

private:
	std::shared_ptr<GameState> gameState; // const?

	SDL_Event event;
	std::shared_ptr<Input> input; // unique_ptr?
	bool play;

	std::list<std::shared_ptr<SelectableObject>> selection;

	//std::shared_ptr<Faction> faction;
};
