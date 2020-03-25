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

	virtual void action(const std::shared_ptr<Selectable>& _actor) {}
	virtual void action(const std::shared_ptr<Selectable>& _actor, const std::shared_ptr<Selectable>& _target) {}
	virtual void action(const std::shared_ptr<Selectable>& _actor, const glm::vec2& _position) {}

protected:
	std::string name;
	std::string description;
	// Icon
	SDL_Keycode hotkey;
	Type type;
};

#endif // COMMAND_H
