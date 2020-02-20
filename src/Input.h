#include <list>

#include "SDL2/SDL_events.h"

class Input
{
public:
	// Keyboard
	bool isKeyHeld(const SDL_Keycode& _key);
	bool isKeyPressed(const SDL_Keycode& _key);
	bool isKeyReleased(const SDL_Keycode& _key);

	// Mouse
	bool isMouseHeld(const int& _button);
	bool isMousePressed(const int& _button);
	bool isMouseReleased(const int& _button);
	int getMouseX();
	int getMouseY();

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
	int mouseX;
	int mouseY;
};
