#include "Engine.h"

class SelectionManager : public Component
{
public:
	void addSelectableEntity(const std::shared_ptr<Entity>& _entity);

private:
	void onUpdate();

	const float nodeSize = 50.0f;

	std::list<std::shared_ptr<Entity>> selectableEntities;
	//std::list<std::shared_ptr<Navigation>> selectableUnits; // This would get around calling getComponent<>() on click
	std::list<std::shared_ptr<Entity>> selection;
};
