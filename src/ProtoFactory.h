#include "SDL2/SDL_render.h"

#include "Building.h"

class ProtoFactory : public Building
{
	void draw(SDL_Renderer* _renderer);
	void onLeftClick();
};
