#include "Constants.h"
#include "Engine.h"

#include <array>

class Command;
class Selectable;

class CommandManager : public Component
{
public:
	void setCommands(const std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows>& _commands);
	void setTarget(const std::shared_ptr<Selectable>& _target);

private:
	void onStart();
	void onUpdate();
	void onDraw(SDL_Renderer* _renderer);

	// Shortcut pointer to Core::Input
	std::shared_ptr<Input> input;

	// Consider fixed size arrays instead of vectors
	std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows> commands;
	SDL_Rect cardPosition;
	SDL_Rect commandPosition;
};
