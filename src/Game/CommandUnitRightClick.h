#include "Command.h"

class CommandUnitRightClick : public Command
{
public:
	void action(const std::shared_ptr<Entity>& _actor, const std::shared_ptr<Entity>& _target);
};
