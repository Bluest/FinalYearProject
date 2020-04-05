#include "CommandCreateUnit.h"
#include "ProtoFactory.h"

void CommandCreateUnit::action(const std::shared_ptr<Entity>& _actor, const glm::vec2& _position, const std::shared_ptr<Entity>& _target)
{
	_actor->getComponent<ProtoFactory>()->createUnit();
}
