#include "Engine.h"

class Map;

class Navigation : public Component
{
public:
	void setMap(const std::shared_ptr<Map>& _map);
	void move(const glm::vec2& _destination);

private:
	void onStart();
	void onUpdate();

	void updateEntityPosition();

	std::shared_ptr<Map> map;

	glm::vec2 position;
	std::list<glm::vec2> path;
};
