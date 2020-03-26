#include "Command.h"

class CommandCreateUnit : public Command
{
public:
	void action(const std::shared_ptr<Selectable>& _actor);
};
