#include "CommandCreateUnit.h"
#include "ProtoFactory.h"

void CommandCreateUnit::action(const std::shared_ptr<Entity>& _actor)
{
	_actor->getComponent<ProtoFactory>()->createUnit();
}
