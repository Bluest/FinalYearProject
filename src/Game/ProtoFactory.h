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

	// May need a pointer to the Map to create units and set Node::walkable

	// Drawing values
	glm::vec2 position;
	float size;
	SDL_FRect rect;
	float circleSize;
};
