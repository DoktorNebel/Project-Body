#include "GameMenus.h"

#include "Button.h"

namespace bg
{
    void createMenus()
    {
        se::Engine::getMenu()->addMenu("Start");
        se::Engine::getMenu()->addMenu("Main");
        se::Engine::getMenu()->addMenu("Options");
        se::Engine::getMenu()->addMenu("Pause");

        se::Engine::getMenu()->addElement("Start", "StartButton", new se::Button(se::Sprite(), se::Text(se::Content::getFont("wendy.ttf"), "Start", se::Vector2(0, -100))));
    }
}