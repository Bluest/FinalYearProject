#include "Command.h"

class CommandMove : public Command
{
public:
	void action(const std::shared_ptr<Selectable>& _actor, const glm::vec2& _position);
};
