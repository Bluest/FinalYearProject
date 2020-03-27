#include "CommandCreateUnit.h"
#include "ProtoFactory.h"
#include "Selectable.h"

void CommandCreateUnit::action(const std::shared_ptr<Selectable>& _actor)
{
	_actor->pubEntity()->getComponent<ProtoFactory>()->createUnit();
}
