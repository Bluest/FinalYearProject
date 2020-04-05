#include "CommandMove.h"
#include "Navigation.h"

void CommandMove::action(const std::shared_ptr<Entity>& _actor, const glm::vec2& _position, const std::shared_ptr<Entity>& _target)
{
	_actor->getComponent<Navigation>()->move(_position);
}
