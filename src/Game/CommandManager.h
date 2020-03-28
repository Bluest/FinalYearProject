#include <array>

#include "Engine.h"

#include "Constants.h"

class Command;

class CommandManager : public Component
{
public:
	void setSelection(const std::shared_ptr<std::list<std::shared_ptr<Entity>>>& _selection);
	void setCommands(const std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows>& _commands);

private:
	void onStart();
	void onUpdate();
	void onDraw(SDL_Renderer* _renderer);

	// Shortcut pointer to Core::Input
	std::shared_ptr<Input> input;

	// Pointer to SelectionManager::selection
	std::shared_ptr<std::list<std::shared_ptr<Entity>>> selection;

	std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows> commands;
	SDL_Rect panelPosition;
	SDL_Rect commandPosition;
};
