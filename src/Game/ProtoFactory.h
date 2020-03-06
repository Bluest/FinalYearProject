#include "Engine.h"

class GameState;

class ProtoFactory : public Component
{
public:
	void createUnit();

private:
	void onStart();
	void onDraw(SDL_Renderer* _renderer);

	const float nodeSize = 25.0f;

	// Drawing values
	glm::vec2 position;
	float size;
	SDL_FRect rect;
	float circleSize;
};
