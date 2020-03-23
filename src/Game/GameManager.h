#include "Engine.h"

class Selectable;

class GameManager : public Component
{
public:
	void addSelectable(const std::shared_ptr<Selectable>& _selectable);

	std::list<std::shared_ptr<Selectable>> getSelectables();

private:
	// onStart() { map = getEntity()->getComponent<Map>() }

	std::list<std::shared_ptr<Selectable>> selectables;
};
