#include <array>
#include <vector>

#include "Engine.h"

#include "Constants.h"

class Command;
class GameManager;

class InputManager : public Component
{
public:
	enum class State
	{
		SELECT,
		TARGET,
		AIM
	};

	void setGameManager(const std::shared_ptr<GameManager>& _gameManager);

private:
	void onStart();
	void onUpdate();

	std::shared_ptr<GameManager> gameManager;
	std::shared_ptr<Input> input;

	State state;
	std::list<std::shared_ptr<Entity>> selection;
	std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows> commands;

	// UI
	void onDraw(SDL_Renderer* _renderer);

	SDL_Rect panelPosition;
	SDL_Rect commandPosition;
};
