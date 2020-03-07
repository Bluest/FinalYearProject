#include "Engine.h"

class CommandManager : public Component
{
private:
	void onStart();
	void onUpdate();

	// Shortcut pointer to Core::Input
	std::shared_ptr<Input> input;


};
