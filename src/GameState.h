#include <list>
#include <memory>

#include "glm/vec2.hpp"
#include "SDL2/SDL_render.h"

class Map;
class Object;
class SelectableObject;

class GameState
{
public:
	GameState(const std::shared_ptr<Map>& _map);

	void update();
	void draw(SDL_Renderer* _renderer);

	void addSO(const std::shared_ptr<SelectableObject>& _so);
	std::shared_ptr<SelectableObject> selectObjectAt(const glm::ivec2& _position);

	std::shared_ptr<Map> getMap();

private:
	std::shared_ptr<Map> map;

	std::list<std::shared_ptr<Object>> objects;
	std::list<std::shared_ptr<SelectableObject>> selectableObjects;
};
