#include "Command.h"

std::list<std::shared_ptr<Entity>> Command::getTargets()
{
	return targets;
}

glm::ivec2 Command::getUISlot()
{
	return uiSlot;
}
