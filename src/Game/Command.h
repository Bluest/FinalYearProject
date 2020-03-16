#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "Engine.h"
#include "glm/vec2.hpp"

class Command
{
public:
	virtual void action() = 0;

	std::list<std::shared_ptr<Entity>> getTargets();
	glm::ivec2 getUISlot();

protected:
	std::list<std::shared_ptr<Entity>> targets;
	std::string name;
	std::string description;
	// Icon
	glm::ivec2 uiSlot;
	SDL_Keycode hotkey;
};

#endif // COMMAND_H
