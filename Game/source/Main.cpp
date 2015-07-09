#include "Engine.h"
#include "BodyGame.h"
#include "GameMenus.h"
#include "InputActions.h"
#include "MenuInputActions.h"
#include "Input.h"
#include "MenuScene.h"

int main()
{
    bg::BodyGame* game = new bg::BodyGame();

    bg::MenuScene* menuScene = new bg::MenuScene();

	se::EngineSettings settings;
    settings.fullscreen = false;
    settings.renderResolutionWidth = 1280;
    settings.renderResolutionHeight = 720;
	settings.screenResolutionWidth = 1280;
	settings.screenResolutionHeight = 720;
    se::Engine::initialize(menuScene, &bg::createMenus, &bg::createFunctionality, settings);

    se::Engine::getMenu()->changeMenu("Start");

    se::Input::bindKeyboardKeyAction(se::InputAction::MenuLeft, sf::Keyboard::Left);
    se::Input::bindKeyboardKeyAction(se::InputAction::MenuRight, sf::Keyboard::Right);
    se::Input::bindKeyboardKeyAction(se::InputAction::MenuUp, sf::Keyboard::Up);
    se::Input::bindKeyboardKeyAction(se::InputAction::MenuDown, sf::Keyboard::Down);
    se::Input::bindKeyboardKeyAction(se::InputAction::MenuConfirm, sf::Keyboard::Return);
    se::Input::bindKeyboardKeyAction(se::InputAction::MenuBack, sf::Keyboard::Escape);
    se::Input::bindMouseButtonAction(se::InputAction::MenuClick, sf::Mouse::Button::Left);

    se::Input::bindKeyboardKeyAction(bg::InputAction::Left, sf::Keyboard::Left);
    se::Input::bindKeyboardKeyAction(bg::InputAction::Right, sf::Keyboard::Right);
    se::Input::bindKeyboardKeyAction(bg::InputAction::Up, sf::Keyboard::Up);
    se::Input::bindKeyboardKeyAction(bg::InputAction::Down, sf::Keyboard::Down);
    se::Input::bindKeyboardKeyAction(bg::InputAction::Shoot, sf::Keyboard::E);
    se::Input::bindKeyboardKeyAction(bg::InputAction::StickyShot, sf::Keyboard::Space);
    se::Input::bindKeyboardKeyAction(bg::InputAction::FasterCheat, sf::Keyboard::C);
    se::Input::bindKeyboardKeyAction(bg::InputAction::Medicine1, sf::Keyboard::Num1);
    se::Input::bindKeyboardKeyAction(bg::InputAction::Medicine2, sf::Keyboard::Num2);
    se::Input::bindKeyboardKeyAction(bg::InputAction::Medicine3, sf::Keyboard::Num3);

	se::Input::bindJoystickAxisAction(se::InputAction::MenuLeft, 0, sf::Joystick::PovX, false, true);
	se::Input::bindJoystickAxisAction(se::InputAction::MenuRight, 0, sf::Joystick::PovX, true, true);
	se::Input::bindJoystickAxisAction(se::InputAction::MenuUp, 0, sf::Joystick::PovY, false, true);
	se::Input::bindJoystickAxisAction(se::InputAction::MenuDown, 0, sf::Joystick::PovY, true, true);
	se::Input::bindJoystickButtonAction(se::InputAction::MenuConfirm, 0, 0, true);
	se::Input::bindJoystickAxisAction(bg::InputAction::Left, 0, sf::Joystick::X, false, true);
	se::Input::bindJoystickAxisAction(bg::InputAction::Right, 0, sf::Joystick::X, true, true);
	se::Input::bindJoystickAxisAction(bg::InputAction::Up, 0, sf::Joystick::Y, false, true);
	se::Input::bindJoystickAxisAction(bg::InputAction::Down, 0, sf::Joystick::Y, true, true);
	se::Input::bindJoystickButtonAction(bg::InputAction::Shoot, 0, 0, true);
	se::Input::bindJoystickAxisAction(bg::InputAction::StickyShot, 0, sf::Joystick::Z, true, true);

    se::Engine::run();

    return 0;
}