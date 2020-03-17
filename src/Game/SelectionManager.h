#include "Engine.h"

class CommandManager;
class Input;

class SelectionManager : public Component
{
public:
	void addSelectableEntity(const std::shared_ptr<Entity>& _entity);

	void setCommandManager(const std::shared_ptr<CommandManager>& _commandManager);

private:
	void onStart();
	void onUpdate();

	std::shared_ptr<CommandManager> commandManager;
	std::shared_ptr<Input> input;

	std::list<std::shared_ptr<Entity>> selectableEntities;
	//std::list<std::shared_ptr<Navigation>> selectableUnits; // This would get around calling getComponent<>() on click
	// In which case, use a struct that stores the pointer to the entity, as well as pointers to its components
	// Have a list of that struct, instead of a list for each entity
	std::list<std::shared_ptr<Entity>> selection;
};
