#include "Engine.h"
#include "glm/vec2.hpp"

class Map;

class GameManager : public Component
{
public:
	void onInit();

	void addEntity(const std::shared_ptr<Entity>& _entity);
	std::shared_ptr<Entity> createUnit(const glm::vec2& _position);
	std::shared_ptr<Entity> getEntityAt(const SDL_Point& _position);

	std::list<std::shared_ptr<Entity>> getEntities();

private:
	std::shared_ptr<Map> map;

	// Should this be a pointer to a list instead? Faster copying?
	std::list<std::shared_ptr<Entity>> entities;
};
