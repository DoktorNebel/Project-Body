#include "GameMenus.h"

#include "Button.h"
#include "IMenuElement.h"
#include "MenuSystem.h"

namespace bg
{
    void createMenus()
    {
        se::Engine::getMenu()->addMenu("Start");
        se::Engine::getMenu()->addMenu("Main");
        se::Engine::getMenu()->addMenu("Options");
        se::Engine::getMenu()->addMenu("Pause");

        se::Engine::getMenu()->addElement("Start", "StartButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Start", se::Vector2(0, -100)), false));


        se::Engine::getMenu()->addElement("Main", "StartButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Start", se::Vector2(-100, 100)), false));

        se::Engine::getMenu()->addElement("Main", "OptionsButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Options", se::Vector2(-100, 0)), false));

        se::Engine::getMenu()->addElement("Main", "QuitButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Quit", se::Vector2(-100, -100)), false));
    }


    void createFunctionality()
    {
        se::Engine::getMenu()->getElement("Main", "StartButton")->setNeighbours(0, 0, 0, se::Engine::getMenu()->getElement("Main", "OptionsButton"));
        se::Engine::getMenu()->getElement("Main", "OptionsButton")->setNeighbours(0, 0, se::Engine::getMenu()->getElement("Main", "StartButton"), se::Engine::getMenu()->getElement("Main", "QuitButton"));
        se::Engine::getMenu()->getElement("Main", "QuitButton")->setNeighbours(0, 0, se::Engine::getMenu()->getElement("Main", "OptionsButton"), 0);

        se::Engine::getMenu()->attachCallback("Start", "StartButton", "onPress", &startButtonFunction);
        se::Engine::getMenu()->attachCallback("Start", "StartButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Start", "StartButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Main", "StartButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "StartButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Main", "OptionsButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "OptionsButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Main", "QuitButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "QuitButton", "onUnhighlight", &unhighlightFunction);
    }


    void startButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        menuSystem->changeMenu("Main");
    }


    void highlightFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->text.setColor(se::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    }


    void unhighlightFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->text.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }
}