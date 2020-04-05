#include "Command.h"

void Command::action(const std::shared_ptr<Entity>& _actor, const glm::vec2& _position, const std::shared_ptr<Entity>& _target)
{

}

Command::Type Command::getType()
{
	return type;
}
