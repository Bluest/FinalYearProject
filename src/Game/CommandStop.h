#include "Command.h"

class CommandStop : public Command
{
public:
	void action(const std::shared_ptr<Selectable>& _target);
};
