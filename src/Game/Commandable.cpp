#include "Commandable.h"

void Commandable::addCommand(const std::shared_ptr<Command>& _command, const int& _slotRow, const int& _slotColumn)
{
	commands[_slotRow][_slotColumn] = _command;
}

bool Commandable::hasCommand(const std::shared_ptr<Command>& _command)
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

std::array<std::array<std::shared_ptr<Command>, 3>, 2> Commandable::getCommands()
{
	return commands;
}
