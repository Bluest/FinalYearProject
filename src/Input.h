#include <list>

#include "SDL2/SDL_events.h"
#include "glm/vec2.hpp"

class Input
{
public:
	// Keyboard
	bool keyHold(const SDL_Keycode& _key);
	bool keyPress(const SDL_Keycode& _key);
	bool keyRelease(const SDL_Keycode& _key);

	// Mouse
	bool mouseHold(const int& _button);
	bool mousePress(const int& _button);
	bool mouseRelease(const int& _button);
	glm::ivec2 mousePosition();

	bool processInput(SDL_Event* _event);

private:
	void processKeyDown(const SDL_Keycode& _key);
	void processKeyUp(const SDL_Keycode& _key);
	void processMouseDown(const int& _button);
	void processMouseUp(const int& _button);

	// Keyboard
	std::list<SDL_Keycode> keysHeld;
	std::list<SDL_Keycode> keysPressed;
	std::list<SDL_Keycode> keysReleased;

	// Mouse
	std::list<int> mouseHeld;
	std::list<int> mousePressed;
	std::list<int> mouseReleased;
};
