#include "Engine.h"

class Navigation : public Component
{
public:
	void setPath(const std::list<glm::vec2>& _path);

private:
	void onUpdate();

	std::list<glm::vec2> path;
};
