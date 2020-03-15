#include "Engine.h"

#include <vector>

class Command;

class CommandManager : public Component
{
public:
	void setCommands(const std::vector<std::vector<std::shared_ptr<Command>>>& _commands);

private:
	void onStart();
	void onUpdate();
	void onDraw(SDL_Renderer* _renderer);

	// Shortcut pointer to Core::Input
	std::shared_ptr<Input> input;

	std::vector<std::vector<std::shared_ptr<Command>>> commands;
	SDL_Rect cardPosition;
};
