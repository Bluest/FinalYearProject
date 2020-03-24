#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "Engine.h"

class Selectable;

class Command
{
public:
	virtual void action(const std::shared_ptr<Selectable>& _target) = 0;

protected:
	std::string name;
	std::string description;
	// Icon
	SDL_Keycode hotkey;
};

#endif // COMMAND_H
