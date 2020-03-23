#include "Constants.h"
#include "Engine.h"

#include <array>

class Command;
class Selectable;

class CommandManager : public Component
{
public:
	void setSelection(const std::shared_ptr<std::list<std::shared_ptr<Selectable>>>& _selection);
	void setCommands(const std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows>& _commands);

private:
	void onStart();
	void onUpdate();
	void onDraw(SDL_Renderer* _renderer);

	// Shortcut pointer to Core::Input
	std::shared_ptr<Input> input;

	// Pointer to SelectionManager::selection
	std::shared_ptr<std::list<std::shared_ptr<Selectable>>> selection;

	std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows> commands;
	SDL_Rect panelPosition;
	SDL_Rect commandPosition;
};
