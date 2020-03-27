#include "Engine.h"
#include "glm/vec2.hpp"

class GameManager;

class ProtoFactory : public Component
{
public:
	void createUnit();

	void setGameManager(const std::shared_ptr<GameManager>& _gameManager);

private:
	void onStart();
	void onDraw(SDL_Renderer* _renderer);

	std::weak_ptr<GameManager> gameManager;

	// Drawing values
	glm::vec2 position;
	float size;
	SDL_FRect rect;
	float circleSize;
};
