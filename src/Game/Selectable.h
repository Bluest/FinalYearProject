#include "Engine.h"

class Selectable : public Component
{
public:
	bool isClicked(const SDL_Point& _clickPosition);

private:
	const float nodeSize = 25.0f;
};
