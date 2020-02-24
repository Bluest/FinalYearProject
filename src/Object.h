#ifndef OBJECT_H
#define OBJECT_H

#include "SDL2/SDL_render.h"

class Object
{
public:
	virtual void update() {}
	virtual void draw(SDL_Renderer* _renderer) {}
	
	virtual void onLeftClick() {}
	virtual void onRightClick() {}
};

#endif // OBJECT_H
