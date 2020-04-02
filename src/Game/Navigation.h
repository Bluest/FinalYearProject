#include "Engine.h"
#include "glm/vec2.hpp"

class Map;

class Navigation : public Component
{
public:
	void onInit();

	void move(const glm::vec2& _destination);
	void stop();

	void setMap(const std::weak_ptr<Map>& _map);

private:
	void onUpdate();

	void moveToWaypoint();
	void updateEntityPosition();

	std::weak_ptr<Map> map;

	float speed;
	glm::vec2 position;
	glm::vec2 step;
	std::list<glm::vec2> path;
	std::list<glm::vec2>::iterator waypoint;
	bool nextWaypoint;
};
