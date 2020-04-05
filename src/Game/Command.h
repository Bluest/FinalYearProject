#ifndef COMMAND_H
#define COMMAND_H

#include <string>

#include "Engine.h"
#include "glm/vec2.hpp"

class Selectable;

class Command
{
public:
	enum class Type
	{
		INSTANT,
		TARGETED,
		AIMED
	};

	virtual void action(const std::shared_ptr<Entity>& _actor, const glm::vec2& _position, const std::shared_ptr<Entity>& _target);

	Type getType();

protected:
	std::string name;
	std::string description;
	// Icon
	SDL_Keycode hotkey;
	Type type;
};

#endif // COMMAND_H
