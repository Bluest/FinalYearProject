#include "Selectable.h"

std::shared_ptr<Entity> Selectable::pubEntity()
{
	return getEntity();
}

void Selectable::addTag(const Tag& _tag)
{
	tags.push_back(_tag);
}

bool Selectable::hasTag(const Tag& _tag)
{
	for (auto it = tags.begin(); it != tags.end(); ++it)
	{
		if (*it == _tag)
		{
			return true;
		}
	}

	return false;
}

void Selectable::addCommand(const std::shared_ptr<Command>& _command, const int& _slotRow, const int& _slotColumn)
{
	commands[_slotRow][_slotColumn] = _command;
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
