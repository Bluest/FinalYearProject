#include "CommandUnitRightClick.h"
#include "Navigation.h"

void CommandUnitRightClick::action(const std::shared_ptr<Entity>& _actor, const glm::vec2& _position, const std::shared_ptr<Entity>& _target)
{
	if (_target)
	{
		// Attack
	}
	else
	{
		_actor->getComponent<Navigation>()->move(_position);
	}
}
