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
        se::Input::bindKeyboardKeyAction(InputAction::StickyShot, sf::Keyboard::Space);
        se::Input::bindKeyboardKeyAction(InputAction::FasterCheat, sf::Keyboard::C);
        se::Input::bindKeyboardKeyAction(InputAction::Medicine1, sf::Keyboard::Num1);
        se::Input::bindKeyboardKeyAction(InputAction::Medicine2, sf::Keyboard::Num2);
        se::Input::bindKeyboardKeyAction(InputAction::Medicine3, sf::Keyboard::Num3);
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