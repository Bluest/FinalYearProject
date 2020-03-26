#include "CommandMove.h"
#include "Navigation.h"
#include "Selectable.h"

void CommandMove::action(const std::shared_ptr<Selectable>& _actor, const glm::vec2& _position)
{
	_actor->pubEntity()->getComponent<Navigation>()->move(_position);
}
