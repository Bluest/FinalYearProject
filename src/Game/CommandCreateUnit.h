#include "Command.h"

class CommandCreateUnit : public Command
{
public:
	void action(const std::shared_ptr<Entity>& _actor);
};
