#include "Engine.h"

class CircleRenderer : public Component
{
private:
	void onDraw(SDL_Renderer* _renderer);

	const float nodeSize = 25.0f;
};
