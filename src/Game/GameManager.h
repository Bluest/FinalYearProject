#include "Engine.h"

class Map;
class Selectable;

class GameManager : public Component
{
public:
	void addSelectable(const std::shared_ptr<Selectable>& _selectable);
	std::shared_ptr<Entity> createUnit();

	std::list<std::shared_ptr<Selectable>> getSelectables();

private:
	void onStart();

	std::shared_ptr<Map> map;

	// Should this be a pointer to a list instead? Faster copying?
	std::list<std::shared_ptr<Selectable>> selectables;
};
