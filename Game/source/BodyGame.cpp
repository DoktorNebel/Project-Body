#include "BodyGame.h"

#include "MathFunctions.h"
#include "Input.h"
#include "Content.h"
#include "InputActions.h"
#include "MenuInputActions.h"

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

        se::Input::bindKeyboardKeyAction(se::InputAction::MenuLeft, sf::Keyboard::Left);
        se::Input::bindKeyboardKeyAction(se::InputAction::MenuRight, sf::Keyboard::Right);
        se::Input::bindKeyboardKeyAction(se::InputAction::MenuUp, sf::Keyboard::Up);
        se::Input::bindKeyboardKeyAction(se::InputAction::MenuDown, sf::Keyboard::Down);
        se::Input::bindKeyboardKeyAction(se::InputAction::MenuConfirm, sf::Keyboard::Return);
        se::Input::bindKeyboardKeyAction(se::InputAction::MenuBack, sf::Keyboard::Escape);
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