#include "BodyGame.h"

#include "MathFunctions.h"
#include "Input.h"
#include "Content.h"
#include "InputActions.h"

namespace bg
{
	BodyGame::BodyGame()
	{

	}


	BodyGame::~BodyGame()
	{

	}


	void BodyGame::initialize()
    {
        this->level.initialize("", this->engine);

        se::Input::bindKeyboardKeyAction(InputActions::Left, sf::Keyboard::Left);
        se::Input::bindKeyboardKeyAction(InputActions::Right, sf::Keyboard::Right);
        se::Input::bindKeyboardKeyAction(InputActions::Up, sf::Keyboard::Up);
        se::Input::bindKeyboardKeyAction(InputActions::Down, sf::Keyboard::Down);
        se::Input::bindKeyboardKeyAction(InputActions::Shoot, sf::Keyboard::E);
	}


	void BodyGame::update(float elapsedTime)
	{
        this->level.update(elapsedTime);
	}


	void BodyGame::draw()
	{
        this->level.draw();
	}


	void BodyGame::close()
	{

	}
}