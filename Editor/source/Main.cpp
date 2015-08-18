#include "Engine.h"
#include "StartScene.h"
#include "EditorMenus.h"
#include "Input.h"
#include "MenuInputActions.h"
#include "InputActions.h"
#include "EditorInputActions.h"

int main()
{
    be::StartScene* scene = new be::StartScene();

    se::EngineSettings settings;
    settings.fullscreen = false;
    settings.renderResolutionWidth = 1280;
    settings.renderResolutionHeight = 720;
    settings.screenResolutionWidth = 1280;
    settings.screenResolutionHeight = 720;

    se::Engine::initialize(scene, &be::createMenus, &be::createFunctionality, settings);

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

    se::Input::bindKeyboardKeyAction(be::InputActions::CameraLeft, sf::Keyboard::A);
    se::Input::bindKeyboardKeyAction(be::InputActions::CameraRight, sf::Keyboard::D);
    se::Input::bindKeyboardKeyAction(be::InputActions::CameraUp, sf::Keyboard::W);
    se::Input::bindKeyboardKeyAction(be::InputActions::CameraDown, sf::Keyboard::S);
    se::Input::bindMouseButtonAction(be::InputActions::DeleteTile, sf::Mouse::Button::Right);

    se::Engine::run();

    return 0;
}