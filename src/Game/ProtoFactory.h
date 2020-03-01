#include <memory>

#include "glm/vec2.hpp"
#include "SDL2/SDL_render.h"

#include "Building.h"

class GameState;

class ProtoFactory : public Building
{
public:
	ProtoFactory(/*Type*/const float& _size, const glm::vec2& _position, const std::shared_ptr<GameState>& _gameState);

	void draw(SDL_Renderer* _renderer);
	void onLeftClick();

private:
	std::weak_ptr<GameState> gameState;
	SDL_FRect rect;
};
