#include "EditorMenus.h"

#include "Button.h"
#include "Slider.h"
#include "IMenuElement.h"
#include "MenuSystem.h"
#include "EditorScene.h"

namespace be
{
    void createMenus()
    {
        se::Engine::getMenu()->addMenu("Start");
        se::Engine::getMenu()->addMenu("ChooseBackground");
        se::Engine::getMenu()->addMenu("Editor");

        se::Engine::getMenu()->addElement("Start", "NewButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "New", se::Vector2(0, 50)), false));
        se::Engine::getMenu()->addElement("Start", "LoadButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Load", se::Vector2(0, -50)), false));


        se::Engine::getMenu()->addElement("ChooseBackground", "Text", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Choose Background", se::Vector2(0, 200)), false));
        se::Engine::getMenu()->addElement("ChooseBackground", "FleshButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Flesh", se::Vector2(0, 50)), false));
        se::Engine::getMenu()->addElement("ChooseBackground", "SlimeButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Slime", se::Vector2(0, -50)), false));
        se::Engine::getMenu()->addElement("ChooseBackground", "PusButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Pus", se::Vector2(0, -150)), false));
        se::Engine::getMenu()->addElement("ChooseBackground", "NervesButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Nerves", se::Vector2(0, -250)), false));


        se::Engine::getMenu()->addElement("Editor", "NewButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "New", se::Vector2(-550, 300)), false));
        se::Engine::getMenu()->addElement("Editor", "SaveButton", new se::Button(se::Content::getSprite("Pixel"), se::Text(se::Content::getFont("wendy.ttf"), "Save", se::Vector2(-400, 300)), false));
        se::Engine::getMenu()->addElement("Editor", "TimeSlider", new se::Slider(se::Content::getSprite("Slider"), se::Content::getSprite("SliderSlider"), se::Content::getFont("wendy.ttf"), se::Vector2(-200.0f, -300.0f), 0.0f, 120.0f, 0.001f, 0.0f));

        se::Engine::getMenu()->data = new be::MenuData();
        ((MenuData*)se::Engine::getMenu()->data)->currentEnemy = "";
        ((MenuData*)se::Engine::getMenu()->data)->currentTile = "";
        ((MenuData*)se::Engine::getMenu()->data)->currentTime = 0.0f;
    }

    void createFunctionality()
    {
        se::Engine::getMenu()->attachCallback("Start", "NewButton", "onPress", &newButtonFunction);
        se::Engine::getMenu()->attachCallback("Start", "NewButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Start", "NewButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Start", "LoadButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Start", "LoadButton", "onUnhighlight", &unhighlightFunction);


        se::Engine::getMenu()->attachCallback("ChooseBackground", "FleshButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("ChooseBackground", "FleshButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("ChooseBackground", "FleshButton", "onPress", &backgroundButtonFunction);

        se::Engine::getMenu()->attachCallback("ChooseBackground", "SlimeButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("ChooseBackground", "SlimeButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("ChooseBackground", "SlimeButton", "onPress", &backgroundButtonFunction);

        se::Engine::getMenu()->attachCallback("ChooseBackground", "PusButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("ChooseBackground", "PusButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("ChooseBackground", "PusButton", "onPress", &backgroundButtonFunction);

        se::Engine::getMenu()->attachCallback("ChooseBackground", "NervesButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("ChooseBackground", "NervesButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("ChooseBackground", "NervesButton", "onPress", &backgroundButtonFunction);


        se::Engine::getMenu()->attachCallback("Editor", "NewButton", "onPress", &newButtonFunction);
        se::Engine::getMenu()->attachCallback("Editor", "NewButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Editor", "NewButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Editor", "SaveButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Editor", "SaveButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Editor", "SaveButton", "onPress", &saveButtonFunction);

        se::Engine::getMenu()->attachCallback("Editor", "TimeSlider", "onValueChange", &timeSliderFunction);
    }


    void newButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        menuSystem->changeMenu("ChooseBackground");
    }


    void highlightFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->text.setColor(se::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    }


    void unhighlightFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->text.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }


    void highlightSpriteFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->sprite.setColor(se::Vector4(1.5f, 1.5f, 1.5f, 1.0f));
    }


    void unhighlightSpriteFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->sprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }


    void backgroundButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        std::string prefix = "";
        if (((se::Button*)sender)->text.getText() == "Flesh")
        {
            ((be::MenuData*)se::Engine::getMenu()->data)->levelType = bc::Tileset::Flesh;
        }
        else if (((se::Button*)sender)->text.getText() == "Slime")
        {
            ((be::MenuData*)se::Engine::getMenu()->data)->levelType = bc::Tileset::Slime;
            prefix = "Slime";
        }
        else if (((se::Button*)sender)->text.getText() == "Pus")
        {
            ((be::MenuData*)se::Engine::getMenu()->data)->levelType = bc::Tileset::Pus;
            prefix = "Pus";
        }
        else if (((se::Button*)sender)->text.getText() == "Nerves")
        {
            ((be::MenuData*)se::Engine::getMenu()->data)->levelType = bc::Tileset::Nerves;
            prefix = "Nerves";
        }

        std::vector<std::string> tilenames;
        tilenames.push_back(prefix + "Eck-Links-Oben");
        tilenames.push_back(prefix + "Eck-Links-Unten");
        tilenames.push_back(prefix + "Eck-Rechts-Oben");
        tilenames.push_back(prefix + "Eck-Rechts-Unten");
        tilenames.push_back(prefix + "Gerade-Links");
        tilenames.push_back(prefix + "Gerade-Oben");
        tilenames.push_back(prefix + "Gerade-Rechts");
        tilenames.push_back(prefix + "Gerade-Unten");
        tilenames.push_back(prefix + "Kante-Links-Oben");
        tilenames.push_back(prefix + "Kante-Links-Unten");
        tilenames.push_back(prefix + "Kante-Rechts-Oben");
        tilenames.push_back(prefix + "Kante-Rechts-Unten");
        tilenames.push_back(prefix + "S-Kurve-Links-1");
        tilenames.push_back(prefix + "S-Kurve-Links-2");
        tilenames.push_back(prefix + "S-Kurve-Rechts-1");
        tilenames.push_back(prefix + "S-Kurve-Rechts-2");
        tilenames.push_back(prefix + "Mitte");

        int y1 = 0;
        int y2 = 0;
        for (unsigned int i = 0; i < tilenames.size(); ++i)
        {
            se::Sprite sprite = se::Content::getSprite(tilenames[i]);
            sprite.setScale(se::Vector2(0.5f, 0.5f));
            sprite.setPosition(sprite.getWidth() < 100.0f ? se::Vector2(530, 300 - y1) : se::Vector2(600, 300 - y2));
            se::Button* button = new se::Button(sprite, se::Text(se::Content::getFont("wendy.ttf"), tilenames[i], se::Vector2(), se::Vector2()), true);
            button->doInitialize(se::Engine::getMenu(), false);
            se::Engine::getMenu()->addElement("Editor", tilenames[i], button);
            button->attachCallback("onHighlight", &highlightSpriteFunction);
            button->attachCallback("onUnhighlight", &unhighlightSpriteFunction);
            button->attachCallback("onPress", &tileButtonFunction);

            y1 += sprite.getWidth() < 100.0f ? (int)(sprite.getHeight() * 0.6f) : 0;
            y2 += sprite.getWidth() < 100.0f ? 0 : (int)(sprite.getHeight() * 0.6f);
        }


        std::vector<std::string> enemyNames;
        enemyNames.push_back("Virus1");
        enemyNames.push_back("V1");
        enemyNames.push_back("KillaBug1");
        enemyNames.push_back("Kefer");
        enemyNames.push_back("Popel");
        enemyNames.push_back("ShooterHead");
        enemyNames.push_back("Boss1");

        int y = 0;
        for (unsigned int i = 0; i < enemyNames.size(); ++i)
        {
            se::Sprite sprite = se::Content::getSprite(enemyNames[i]);
            sprite.setPosition(se::Vector2(450, 300 - y));
            se::Button* button = new se::Button(sprite, se::Text(se::Content::getFont("wendy.ttf"), enemyNames[i], se::Vector2(), se::Vector2()), true);
            button->doInitialize(se::Engine::getMenu(), false);
            se::Engine::getMenu()->addElement("Editor", enemyNames[i], button);
            button->attachCallback("onHighlight", &highlightSpriteFunction);
            button->attachCallback("onUnhighlight", &unhighlightSpriteFunction);
            button->attachCallback("onPress", &enemyButtonFunction);

            y += (int)(sprite.getHeight() * 2.0f);
        }

        se::Engine::getMenu()->changeMenu("Editor");
        se::IScene* newScene = new be::EditorScene();
        se::Engine::changeScene(newScene);
    }


    void tileButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((MenuData*)se::Engine::getMenu()->data)->currentTile = ((se::Button*)sender)->text.getText();
        ((MenuData*)se::Engine::getMenu()->data)->currentEnemy = "";
    }


    void enemyButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((MenuData*)se::Engine::getMenu()->data)->currentTile = "";
        ((MenuData*)se::Engine::getMenu()->data)->currentEnemy = ((se::Button*)sender)->text.getText();
    }


    void saveButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((MenuData*)se::Engine::getMenu()->data)->scene->save();
    }


	void loadButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
	{

	}


    void timeSliderFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((MenuData*)se::Engine::getMenu()->data)->currentTime = ((se::Slider*)sender)->getAbsoluteValue();
    }
}