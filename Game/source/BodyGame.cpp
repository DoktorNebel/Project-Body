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
        this->level.initialize("Test");

        se::Input::bindKeyboardKeyAction(InputAction::Left, sf::Keyboard::Left);
        se::Input::bindKeyboardKeyAction(InputAction::Right, sf::Keyboard::Right);
        se::Input::bindKeyboardKeyAction(InputAction::Up, sf::Keyboard::Up);
        se::Input::bindKeyboardKeyAction(InputAction::Down, sf::Keyboard::Down);
        se::Input::bindKeyboardKeyAction(InputAction::Shoot, sf::Keyboard::E);
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