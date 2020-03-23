#include "Engine.h"

class CommandManager;
class GameManager;
class Input;

class SelectionManager : public Component
{
public:
	void setCommandManager(const std::shared_ptr<CommandManager>& _commandManager);
	void setGameManager(const std::shared_ptr<GameManager>& _gameManager);

private:
	void onStart();
	void onUpdate();

	std::shared_ptr<CommandManager> commandManager;
	std::shared_ptr<GameManager> gameManager;
	std::shared_ptr<Input> input;

	std::shared_ptr<std::list<std::shared_ptr<Selectable>>> selection;
};
