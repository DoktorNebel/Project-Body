#include "GameMenus.h"

#include "Button.h"
#include "IMenuElement.h"
#include "MenuSystem.h"
#include "BodyGame.h"
#include "MenuTimer.h"
#include "ProgressBar.h"
#include "UISprite.h"
#include "MenuData.h"

namespace bg
{
    void createMenus()
    {
        se::Engine::getMenu()->addMenu("Start");
        se::Engine::getMenu()->addMenu("Main");
        se::Engine::getMenu()->addMenu("Options");
        se::Engine::getMenu()->addMenu("Pause");
        se::Engine::getMenu()->addMenu("Levels");
        se::Engine::getMenu()->addMenu("Highscores");
        se::Engine::getMenu()->addMenu("UI");

        se::Sprite pixelSprite = se::Content::getSprite("Pixel");
        pixelSprite.setScale(se::Vector2(0.0f, 0.0f));

        //start screen
        se::Engine::getMenu()->addElement("Start", "StartButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Start", se::Vector2(0, -100)), false));

        //main menu
        se::Engine::getMenu()->addElement("Main", "StartButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Start", se::Vector2(-100, 100)), false));

        se::Engine::getMenu()->addElement("Main", "OptionsButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Options", se::Vector2(-100, 0)), false));

        se::Engine::getMenu()->addElement("Main", "QuitButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Quit", se::Vector2(-100, -100)), false));

        //level menu
        se::Text text(se::Content::getFont("wendy.ttf"), "Flesh");
        text.setScale(se::Vector2(0.0f, 0.0f));
        se::Sprite sprite = se::Content::getSprite("FleshLevelButton");
        sprite.setPosition(se::Vector2(-300, 100));
        se::Engine::getMenu()->addElement("Levels", "Flesh", new se::Button(sprite, text, true));

        text.setText("Nerves");
        sprite = se::Content::getSprite("NervesLevelButton");
        sprite.setPosition(se::Vector2(-100, 100));
        se::Engine::getMenu()->addElement("Levels", "Nerves", new se::Button(sprite, text, true));

        text.setText("Slime");
        sprite = se::Content::getSprite("SlimeLevelButton");
        sprite.setPosition(se::Vector2(100, 100));
        se::Engine::getMenu()->addElement("Levels", "Slime", new se::Button(sprite, text, true));

        text.setText("Pus");
        sprite = se::Content::getSprite("PusLevelButton");
        sprite.setPosition(se::Vector2(300, 100));
        se::Engine::getMenu()->addElement("Levels", "Pus", new se::Button(sprite, text, true));

        //UI
        se::Engine::getMenu()->addElement("UI", "BossbarText", new se::UISprite(se::Content::getSprite("BOSS"), se::Vector2(0.0f, 345.0f)));
        for (int i = 0; i < 100; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            se::Engine::getMenu()->addElement("UI", "Bossbar" + std::string(number), new se::UISprite(se::Content::getSprite("BossHP"), se::Vector2(-197.0f + (float)i * 4.0f, 330.0f)));
        }

        se::Engine::getMenu()->addElement("UI", "StickyShotIcon", new se::UISprite(se::Content::getSprite("HUDshot"), se::Vector2(600.0f, -250.0f)));
        se::Engine::getMenu()->addElement("UI", "StickyShot0", new se::UISprite(se::Content::getSprite("U"), se::Vector2(600.0f, -250.0f)));
        se::Engine::getMenu()->addElement("UI", "StickyShot1", new se::UISprite(se::Content::getSprite("LU"), se::Vector2(600.0f, -250.0f)));
        se::Engine::getMenu()->addElement("UI", "StickyShot2", new se::UISprite(se::Content::getSprite("L"), se::Vector2(600.0f, -250.0f)));
        se::Engine::getMenu()->addElement("UI", "StickyShot3", new se::UISprite(se::Content::getSprite("LO"), se::Vector2(600.0f, -250.0f)));
        se::Engine::getMenu()->addElement("UI", "StickyShot4", new se::UISprite(se::Content::getSprite("O"), se::Vector2(600.0f, -250.0f)));
        se::Engine::getMenu()->addElement("UI", "StickyShot5", new se::UISprite(se::Content::getSprite("RO"), se::Vector2(600.0f, -250.0f)));
        se::Engine::getMenu()->addElement("UI", "StickyShot6", new se::UISprite(se::Content::getSprite("R"), se::Vector2(600.0f, -250.0f)));
        se::Engine::getMenu()->addElement("UI", "StickyShot7", new se::UISprite(se::Content::getSprite("RU"), se::Vector2(600.0f, -250.0f)));

        se::Engine::getMenu()->addElement("UI", "BombRingIcon", new se::UISprite(se::Content::getSprite("HUDring"), se::Vector2(600.0f, -320.0f)));
        se::Engine::getMenu()->addElement("UI", "BombRing0", new se::UISprite(se::Content::getSprite("U"), se::Vector2(600.0f, -320.0f)));
        se::Engine::getMenu()->addElement("UI", "BombRing1", new se::UISprite(se::Content::getSprite("LU"), se::Vector2(600.0f, -320.0f)));
        se::Engine::getMenu()->addElement("UI", "BombRing2", new se::UISprite(se::Content::getSprite("L"), se::Vector2(600.0f, -320.0f)));
        se::Engine::getMenu()->addElement("UI", "BombRing3", new se::UISprite(se::Content::getSprite("LO"), se::Vector2(600.0f, -320.0f)));
        se::Engine::getMenu()->addElement("UI", "BombRing4", new se::UISprite(se::Content::getSprite("O"), se::Vector2(600.0f, -320.0f)));
        se::Engine::getMenu()->addElement("UI", "BombRing5", new se::UISprite(se::Content::getSprite("RO"), se::Vector2(600.0f, -320.0f)));
        se::Engine::getMenu()->addElement("UI", "BombRing6", new se::UISprite(se::Content::getSprite("R"), se::Vector2(600.0f, -320.0f)));
        se::Engine::getMenu()->addElement("UI", "BombRing7", new se::UISprite(se::Content::getSprite("RU"), se::Vector2(600.0f, -320.0f)));

        se::Engine::getMenu()->addElement("UI", "Timer", new se::MenuTimer(0.033f));


        se::Engine::getMenu()->data = new MenuData();
    }


    void createFunctionality()
    {
        //neighbours
        se::Engine::getMenu()->getElement("Main", "StartButton")->setNeighbours(0, 0, 0, se::Engine::getMenu()->getElement("Main", "OptionsButton"));
        se::Engine::getMenu()->getElement("Main", "OptionsButton")->setNeighbours(0, 0, se::Engine::getMenu()->getElement("Main", "StartButton"), se::Engine::getMenu()->getElement("Main", "QuitButton"));
        se::Engine::getMenu()->getElement("Main", "QuitButton")->setNeighbours(0, 0, se::Engine::getMenu()->getElement("Main", "OptionsButton"), 0);

        se::Engine::getMenu()->getElement("Levels", "Flesh")->setNeighbours(0, se::Engine::getMenu()->getElement("Levels", "Nerves"), 0, 0);
        se::Engine::getMenu()->getElement("Levels", "Nerves")->setNeighbours(se::Engine::getMenu()->getElement("Levels", "Flesh"), se::Engine::getMenu()->getElement("Levels", "Slime"), 0, 0);
        se::Engine::getMenu()->getElement("Levels", "Slime")->setNeighbours(se::Engine::getMenu()->getElement("Levels", "Nerves"), se::Engine::getMenu()->getElement("Levels", "Pus"), 0, 0);
        se::Engine::getMenu()->getElement("Levels", "Pus")->setNeighbours(se::Engine::getMenu()->getElement("Levels", "Slime"), 0, 0, 0);

        //functionality
        se::Engine::getMenu()->attachCallback("Start", "StartButton", "onPress", &startButtonFunction);
        se::Engine::getMenu()->attachCallback("Start", "StartButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Start", "StartButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Main", "StartButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "StartButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "StartButton", "onPress", &startGameButtonFunction);

        se::Engine::getMenu()->attachCallback("Main", "OptionsButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "OptionsButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Main", "QuitButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "QuitButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "QuitButton", "onPress", &exitButtonFunction);


        se::Engine::getMenu()->attachCallback("Levels", "Flesh", "onHighlight", &highlightFunction2);
        se::Engine::getMenu()->attachCallback("Levels", "Flesh", "onUnhighlight", &unhighlightFunction2);
        se::Engine::getMenu()->attachCallback("Levels", "Flesh", "onPress", &levelButtonFunction);

        se::Engine::getMenu()->attachCallback("Levels", "Nerves", "onHighlight", &highlightFunction2);
        se::Engine::getMenu()->attachCallback("Levels", "Nerves", "onUnhighlight", &unhighlightFunction2);
        se::Engine::getMenu()->attachCallback("Levels", "Nerves", "onPress", &levelButtonFunction);

        se::Engine::getMenu()->attachCallback("Levels", "Slime", "onHighlight", &highlightFunction2);
        se::Engine::getMenu()->attachCallback("Levels", "Slime", "onUnhighlight", &unhighlightFunction2);
        se::Engine::getMenu()->attachCallback("Levels", "Slime", "onPress", &levelButtonFunction);

        se::Engine::getMenu()->attachCallback("Levels", "Pus", "onHighlight", &highlightFunction2);
        se::Engine::getMenu()->attachCallback("Levels", "Pus", "onUnhighlight", &unhighlightFunction2);
        se::Engine::getMenu()->attachCallback("Levels", "Pus", "onPress", &levelButtonFunction);


        se::Engine::getMenu()->attachCallback("UI", "Timer", "onTick", &uiUpdateFunction);

        //hide boss bar
        se::Engine::getMenu()->getElement("UI", "BossbarText")->hide();
        for (int i = 0; i < 100; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            se::Engine::getMenu()->getElement("UI", "Bossbar" + std::string(number))->hide();
        }
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


    void highlightFunction2(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->sprite.setColor(se::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    }


    void unhighlightFunction2(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->sprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }


    void startGameButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        menuSystem->changeMenu("Levels");
    }


    void levelButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((MenuData*)menuSystem->data)->levelName = ((se::Button*)sender)->text.getText();
        menuSystem->changeMenu("UI");
        BodyGame* newScene = new BodyGame();
        se::Engine::changeScene(newScene);
    }


    void exitButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        se::Engine::close();
    }


    void uiUpdateFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        int highest = (int)(((MenuData*)menuSystem->data)->stickyShotCooldown * 8.0f);
        for (int i = 0; i < 8; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            ((se::UISprite*)menuSystem->getElement("UI", "StickyShot" + std::string(number)))->getSprite().setColor(i < highest ? se::Vector4(1.0f, 1.0f, 1.0f, 1.0f) : se::Vector4(1.0f, 1.0f, 1.0f, 0.0f));
        }

        highest = (int)(((MenuData*)menuSystem->data)->bombRingCooldown * 8.0f);
        for (int i = 0; i < 8; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            ((se::UISprite*)menuSystem->getElement("UI", "BombRing" + std::string(number)))->getSprite().setColor(i < highest ? se::Vector4(1.0f, 1.0f, 1.0f, 1.0f) : se::Vector4(1.0f, 1.0f, 1.0f, 0.0f));
        }

        highest = (int)(((MenuData*)menuSystem->data)->bossHealth * 100.0f);
        for (int i = 0; i < 100; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            ((se::UISprite*)menuSystem->getElement("UI", "Bossbar" + std::string(number)))->getSprite().setColor(i < highest ? se::Vector4(1.0f, 1.0f, 1.0f, 1.0f) : se::Vector4(1.0f, 1.0f, 1.0f, 0.0f));
        }
    }
}