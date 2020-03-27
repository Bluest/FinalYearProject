#include "Engine.h"
#include "glm/vec2.hpp"

class Map;
class Selectable;

class GameManager : public Component
{
public:
	void onInit();

	void addSelectable(const std::shared_ptr<Selectable>& _selectable);
	std::shared_ptr<Entity> createUnit(const glm::vec2& _position);

	std::list<std::shared_ptr<Selectable>> getSelectables();

private:
	std::shared_ptr<Map> map;

	// Should this be a pointer to a list instead? Faster copying?
	std::list<std::shared_ptr<Selectable>> selectables;
};
