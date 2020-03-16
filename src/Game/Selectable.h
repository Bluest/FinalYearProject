#include <array>

#include "Engine.h"

class Command;

class Selectable : public Component
{
public:
	void addCommand(const std::shared_ptr<Command>& _command, const int& _slotRow, const int& _slotColumn);
	bool isClicked(const SDL_Point& _clickPosition);

	std::array<std::array<std::shared_ptr<Command>, 3>, 2> getCommands();

private:
	const float nodeSize = 25.0f;

	std::array<std::array<std::shared_ptr<Command>, 3>, 2> commands;
};
