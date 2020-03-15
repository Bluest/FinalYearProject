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

	const size_t slotColumns = 3;
	const size_t slotRows = 2;

	// Shortcut pointer to Core::Input
	std::shared_ptr<Input> input;

	// Consider fixed size arrays instead of vectors
	std::vector<std::vector<std::shared_ptr<Command>>> commands;
	SDL_Rect cardPosition;
	SDL_Rect commandPosition;
};
