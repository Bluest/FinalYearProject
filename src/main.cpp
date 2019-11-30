#include <SDL.h>
#include <iostream>
#include <memory>
#include <cmath>

struct vec2f
{
	float x;
	float y;
};

struct Unit
{
	float size;
	float speed;

	bool moving;
	vec2f pos;
	vec2f dest;
	vec2f dir;

	Unit(float _size, float _speed, float _posX, float _posY)
	{
		size = _size;
		speed = _speed;

		moving = false;
		pos = { _posX, _posY };
		dest = { _posX, _posY };
		dir = { NULL, NULL };
	}

	void draw(SDL_Renderer* _renderer)
	{
		if (moving)
		{
			SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
			SDL_RenderDrawLine(_renderer,
				static_cast<int>(pos.x),
				static_cast<int>(pos.y),
				static_cast<int>(dest.x),
				static_cast<int>(dest.y));
		}

		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		for (float t = 0; t < 2 * M_PI; t += 1.0f / size)
		{
			SDL_RenderDrawPointF(_renderer, pos.x + size * sin(t), pos.y + size * cos(t));
		}
	}

	void update()
	{
		if (moving)
		{
			pos.x += dir.x;
			pos.y += dir.y;

			if (dir.x > 0.0f) { if (pos.x > dest.x) moving = false; }
			else if (dir.x < 0.0f) { if (pos.x < dest.x) moving = false; }

			if (dir.y > 0.0f) { if (pos.y > dest.y) moving = false; }
			else if (dir.y < 0.0f) { if (pos.y < dest.y) moving = false; }

			if (!moving)
			{
				pos.x = dest.x;
				pos.y = dest.y;
			}
		}
	}

	void move()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		dest.x = static_cast<float>(x);
		dest.y = static_cast<float>(y);

		vec2f delta = { dest.x - pos.x, dest.y - pos.y };
		float distance = hypotf(delta.x, delta.y);
		if (distance > 0)
		{
			dir.x = speed * delta.x / distance;
			dir.y = speed * delta.y / distance;
			moving = true;
		}
	}
};

void init(SDL_Window** _window, SDL_Renderer** _renderer)
{
	const int winW = 640;
	const int winH = 480;

	SDL_Init(SDL_INIT_VIDEO);

	*_window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, winW, winH, SDL_WINDOW_SHOWN);
	*_renderer = SDL_CreateRenderer(*_window, -1, SDL_RENDERER_ACCELERATED);
}

int main(int argc, char* argv[])
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	init(&window, &renderer);

	std::shared_ptr<Unit> unit = std::make_shared<Unit>(25.0f, 5.0f, 320.0f, 240.0f);

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_MOUSEBUTTONDOWN:
			{
				switch (event.button.button)
				{
				case SDL_BUTTON_LEFT: unit->moving = false; break;
				case SDL_BUTTON_RIGHT: unit->move(); break;
				}
				break;
			}
			case SDL_QUIT: { quit = true; break; }
			}
		}

		unit->update();

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);
		unit->draw(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
