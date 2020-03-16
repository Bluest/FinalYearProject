#include "Engine.h"

#include <array>

class Command;

class CommandManager : public Component
{
public:
	void setCommands(const std::array<std::array<std::shared_ptr<Command>, 3>, 2>& _commands);
	void setTarget(const std::shared_ptr<Entity>& _target);

private:
	void onStart();
	void onUpdate();
	void onDraw(SDL_Renderer* _renderer);

	// Shortcut pointer to Core::Input
	std::shared_ptr<Input> input;

	// Consider fixed size arrays instead of vectors
	std::array<std::array<std::shared_ptr<Command>, 3>, 2> commands;
	SDL_Rect cardPosition;
	SDL_Rect commandPosition;
};
