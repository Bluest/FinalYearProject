#include "Engine.h"

class Selectable : public Component
{
public:
	bool isClicked(const glm::ivec2& _clickPosition);

private:
	const float nodeSize = 25.0f;
};
