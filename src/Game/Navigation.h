#include "Engine.h"
#include "glm/vec2.hpp"

class Map;

class Navigation : public Component
{
public:
	void move(const glm::vec2& _destination);
	void stop();

	void setMap(const std::shared_ptr<Map>& _map);

private:
	void onStart();
	void onUpdate();

	void moveToWaypoint();
	void updateEntityPosition();

	std::shared_ptr<Map> map;

	float speed;
	glm::vec2 position;
	glm::vec2 step;
	std::list<glm::vec2> path;
	std::list<glm::vec2>::iterator waypoint;
	bool nextWaypoint;
};
