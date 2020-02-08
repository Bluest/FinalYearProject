#include "SDL.h"

struct vec2f
{
	float x;
	float y;
};

class Unit
{
public:
	Unit(float _size, float _speed, float _posX, float _posY);

	void draw(SDL_Renderer* _renderer);
	void update();
	void move();
	void stop();

	vec2f getPos();

private:
	// Stats
	float size;
	float speed;

	// State
	bool moving;
	vec2f pos;
	vec2f dest;
	vec2f step;
};
