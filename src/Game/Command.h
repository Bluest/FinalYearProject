#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "Engine.h"

class Command
{
public:
	virtual void action() = 0;

protected:
	std::string name;
	std::string description;
	// Icon
	SDL_Keycode hotkey;
};

#endif // COMMAND_H
