#include "Selectable.h"

void Selectable::addCommand(const std::shared_ptr<Command>& _command, const int& _slotRow, const int& _slotColumn)
{
	commands[_slotColumn][_slotRow] = _command;
}

bool Selectable::hasCommand(const std::shared_ptr<Command>& _command)
{
	for (size_t y = 0; y < commandSlotRows; ++y)
	{
		for (size_t x = 0; x < commandSlotColumns; ++x)
		{
			if (commands[y][x] == _command)
			{
				return true;
			}
		}
	}

	return false;
}

bool Selectable::isClicked(const SDL_Point& _clickPosition)
{
	// Translate Entity's position from world space to screen space
	glm::vec3 position = getEntity()->transform.position * nodeSize + nodeSize / 2;
	float size = getEntity()->transform.scale.x * nodeSize;

	SDL_Rect clickBox;
	clickBox.x = int(position.x - size / 2);
	clickBox.y = int(position.z - size / 2);
	clickBox.w = int(size);
	clickBox.h = int(size);

	return SDL_PointInRect(&_clickPosition, &clickBox);
}

std::array<std::array<std::shared_ptr<Command>, 3>, 2> Selectable::getCommands()
{
	return commands;
}
