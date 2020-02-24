#include "GameState.h"
#include "Input.h"
#include "Map.h"
#include "Player.h"
#include "SelectableObject.h"

Player::Player(const std::shared_ptr<GameState>& _gameState)
{
	gameState = _gameState;

	event = { 0u };
	input = std::make_shared<Input>();
	play = true;
}

bool Player::handleInput()
{
	// play will equal false if input receives SDL_QUIT
	play = input->processInput(&event);

	if (input->mousePress(SDL_BUTTON_LEFT))
	{
		// What did I click?

		// Single click, single unit
		selection.clear();
		auto blah = gameState->selectObjectAt(input->mousePosition());
		if (blah != nullptr) selection.push_back(blah);

		if (!selection.empty()) printf("Selected %p\n", selection.front().get()); else printf("No selection\n");
	}

	if (input->mousePress(SDL_BUTTON_RIGHT))
	{
		// What did I click?
		// What do I have selected?
		// Below assumes selection of a unit, clicking the ground

		for (auto it = selection.begin(); it != selection.end(); ++it)
		{
			// TODO: Clean up this line lmao
			// ie. (*it)->move(input->mousePosition()) if Unit has a pointer to Map or something
			(*it)->move(gameState->getMap()->findPath((*it)->getPosition(), input->mousePosition()));
		}
	}

	if (input->mousePress(SDL_BUTTON_MIDDLE))
	{
		for (auto it = selection.begin(); it != selection.end(); ++it)
		{
			// if it's a unit, Unit::stop()
			// also depends which object's commands are current
			// command menu is for a unit and has stop? hell yeah
			// command menu is for a building and doesn't? no stoppin'
			//(*it)->stop();
		}
	}

	return play;
}
