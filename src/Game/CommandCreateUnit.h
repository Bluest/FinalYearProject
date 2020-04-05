#include "Command.h"

class CommandCreateUnit : public Command
{
public:
	void action(const std::shared_ptr<Entity>& _actor, const glm::vec2& _position, const std::shared_ptr<Entity>& _target);
};
