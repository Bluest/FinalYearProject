#include <array>

#include "Constants.h"
#include "Engine.h"

class Command;

class Selectable : public Component
{
public:
	std::shared_ptr<Entity> pubEntity();

	void addCommand(const std::shared_ptr<Command>& _command, const int& _slotRow, const int& _slotColumn);
	bool hasCommand(const std::shared_ptr<Command>& _command);

	bool isClicked(const SDL_Point& _clickPosition);

	std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows> getCommands();

private:
	std::array<std::array<std::shared_ptr<Command>, commandSlotColumns>, commandSlotRows> commands;
};
