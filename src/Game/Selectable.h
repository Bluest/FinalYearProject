#include "Engine.h"

class Selectable : public Component
{
public:
	bool isClicked(const SDL_Point& _clickPosition);
};
