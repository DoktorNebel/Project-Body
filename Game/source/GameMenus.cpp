#include "GameMenus.h"

#include "Other\tinydir.h"

#include "Button.h"
#include "IMenuElement.h"
#include "MenuSystem.h"
#include "BodyGame.h"
#include "MenuTimer.h"
#include "ProgressBar.h"
#include "UISprite.h"
#include "UIText.h"
#include "MenuData.h"
#include "Spawner.h"
#include "BodyGame.h"
#include "MenuScene.h"
#include "GameData.h"

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
        se::Engine::getMenu()->addMenu("LevelEnd");

        se::Sprite pixelSprite = se::Content::getSprite("Pixel");
        pixelSprite.setScale(se::Vector2(0.0f, 0.0f));

        //start screen
        se::Engine::getMenu()->addElement("Start", "StartButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Start", se::Vector2(0, -100), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

        //main menu
		se::Engine::getMenu()->addElement("Main", "StartButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Start", se::Vector2(-100, 150), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Main", "HighscoreButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Highscores", se::Vector2(-100, 50), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Main", "OptionsButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Options", se::Vector2(-100, -50), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Main", "QuitButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Quit", se::Vector2(-100, -150), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

        //pause menu
		se::Engine::getMenu()->addElement("Pause", "ResumeButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Resume", se::Vector2(0, 100), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Pause", "RestartButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Restart", se::Vector2(0, 0), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Pause", "MenuButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Main Menu", se::Vector2(0, -100), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

        //level menu
		se::Engine::getMenu()->addElement("Levels", "Flesh", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Flesh", se::Vector2(-400, 150), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Levels", "Nerves", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Nerves", se::Vector2(-400, 50), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Levels", "Slime", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Slime", se::Vector2(-400, -50), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Levels", "Pus", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Pus", se::Vector2(-400, -150), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));


        //highscore menu
		se::Engine::getMenu()->addElement("Highscores", "BackButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Back", se::Vector2(-500, -300), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Highscores", "FleshButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Flesh", se::Vector2(-300, 280), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Highscores", "NervesButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Nerves", se::Vector2(-100, 280), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Highscores", "SlimeButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Slime", se::Vector2(100, 280), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("Highscores", "PusButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Pus", se::Vector2(300, 280), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

        se::Engine::getMenu()->addElement("Highscores", "HighscoreText", new se::UIText(se::Text(se::Content::getFont("wendy.ttf"), "Highscores", se::Vector2(0, 330))));

        for (int i = 0; i < 10; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            se::Engine::getMenu()->addElement("Highscores", "HighscoreName" + std::string(number), new se::UIText(se::Text(se::Content::getFont("wendy.ttf"), "", se::Vector2(-300, 230 - i * 50), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 1.0f), se::Text::Alignment::Left)));

            se::Engine::getMenu()->addElement("Highscores", "Highscore" + std::string(number), new se::UIText(se::Text(se::Content::getFont("wendy.ttf"), "", se::Vector2(300, 230 - i * 50), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 1.0f), se::Text::Alignment::Right)));
        }

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

		//Level end screen
		se::Engine::getMenu()->addElement("LevelEnd", "NextButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Next Level", se::Vector2(500, -300), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

		se::Engine::getMenu()->addElement("LevelEnd", "MenuButton", new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), "Main Menu", se::Vector2(-500, -300), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));

        se::Engine::getMenu()->addElement("LevelEnd", "ScoreText", new se::UIText(se::Text(se::Content::getFont("wendy.ttf"), "Score:", se::Vector2(-300, 250))));

        se::Engine::getMenu()->addElement("LevelEnd", "NameText", new se::UIText(se::Text(se::Content::getFont("wendy.ttf"), "Your Name:", se::Vector2(-300, 150))));

        for (unsigned char c = 65; c < 91; ++c)
        {
            std::string text;
            text += c;
			se::Engine::getMenu()->addElement("LevelEnd", text, new se::Button(pixelSprite, se::Text(se::Content::getFont("wendy.ttf"), text, se::Vector2(-500 + ((c - 65) % 8) * 50, 50 - (c - 65) / 8 * 50), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 0.5f)), false));
        }


		se::Engine::getMenu()->data = new MenuData();
		((MenuData*)se::Engine::getMenu()->data)->playerName[0] = ' ';
		((MenuData*)se::Engine::getMenu()->data)->playerName[1] = ' ';
		((MenuData*)se::Engine::getMenu()->data)->playerName[2] = ' ';
		((MenuData*)se::Engine::getMenu()->data)->playerName[3] = '\0';
        ((MenuData*)se::Engine::getMenu()->data)->currentChar = 0;
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

        se::Engine::getMenu()->attachCallback("Main", "HighscoreButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "HighscoreButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "HighscoreButton", "onPress", &highscoreButtonFunction);

        se::Engine::getMenu()->attachCallback("Main", "OptionsButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "OptionsButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Main", "QuitButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "QuitButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Main", "QuitButton", "onPress", &exitButtonFunction);


        se::Engine::getMenu()->attachCallback("Pause", "ResumeButton", "onPress", &resumeButtonFunction);
        se::Engine::getMenu()->attachCallback("Pause", "ResumeButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Pause", "ResumeButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Pause", "RestartButton", "onPress", &restartButtonFunction);
        se::Engine::getMenu()->attachCallback("Pause", "RestartButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Pause", "RestartButton", "onUnhighlight", &unhighlightFunction);

        se::Engine::getMenu()->attachCallback("Pause", "MenuButton", "onPress", &mainMenuButtonFunction);
        se::Engine::getMenu()->attachCallback("Pause", "MenuButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Pause", "MenuButton", "onUnhighlight", &unhighlightFunction);


        se::Engine::getMenu()->attachCallback("Levels", "Flesh", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Flesh", "onHighlight", &changeBackgroundFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Flesh", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Flesh", "onPress", &levelButtonFunction);

        se::Engine::getMenu()->attachCallback("Levels", "Nerves", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Nerves", "onHighlight", &changeBackgroundFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Nerves", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Nerves", "onPress", &levelButtonFunction);

        se::Engine::getMenu()->attachCallback("Levels", "Slime", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Slime", "onHighlight", &changeBackgroundFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Slime", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Slime", "onPress", &levelButtonFunction);

        se::Engine::getMenu()->attachCallback("Levels", "Pus", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Pus", "onHighlight", &changeBackgroundFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Pus", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Levels", "Pus", "onPress", &levelButtonFunction);


        se::Engine::getMenu()->attachCallback("Highscores", "FleshButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "FleshButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "FleshButton", "onPress", &highscoreButtonFunction);

        se::Engine::getMenu()->attachCallback("Highscores", "NervesButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "NervesButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "NervesButton", "onPress", &highscoreButtonFunction);

        se::Engine::getMenu()->attachCallback("Highscores", "SlimeButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "SlimeButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "SlimeButton", "onPress", &highscoreButtonFunction);

        se::Engine::getMenu()->attachCallback("Highscores", "PusButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "PusButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "PusButton", "onPress", &highscoreButtonFunction);

        se::Engine::getMenu()->attachCallback("Highscores", "BackButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "BackButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("Highscores", "BackButton", "onPress", &backButtonFunction);


        se::Engine::getMenu()->attachCallback("UI", "Timer", "onTick", &uiUpdateFunction);


        se::Engine::getMenu()->attachCallback("LevelEnd", "NextButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("LevelEnd", "NextButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("LevelEnd", "NextButton", "onPress", &nextLevelButtonFunction);
        se::Engine::getMenu()->attachCallback("LevelEnd", "NextButton", "onPress", &saveScoreFunction);

        se::Engine::getMenu()->attachCallback("LevelEnd", "MenuButton", "onHighlight", &highlightFunction);
        se::Engine::getMenu()->attachCallback("LevelEnd", "MenuButton", "onUnhighlight", &unhighlightFunction);
        se::Engine::getMenu()->attachCallback("LevelEnd", "MenuButton", "onPress", &mainMenuButtonFunction);
        se::Engine::getMenu()->attachCallback("LevelEnd", "MenuButton", "onPress", &saveScoreFunction);

        for (unsigned char c = 65; c < 91; ++c)
        {
            std::string text;
            text += c;
            se::Engine::getMenu()->attachCallback("LevelEnd", text, "onHighlight", &highlightFunction);
            se::Engine::getMenu()->attachCallback("LevelEnd", text, "onUnhighlight", &unhighlightFunction);
            se::Engine::getMenu()->attachCallback("LevelEnd", text, "onPress", &characterButtonFunction);
        }

        //hide boss bar
        se::Engine::getMenu()->getElement("UI", "BossbarText")->hide();
        for (int i = 0; i < 100; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            se::Engine::getMenu()->getElement("UI", "Bossbar" + std::string(number))->hide();
        }
    }


    void highlightFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->text.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }


    void unhighlightFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->text.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 0.5f));
    }


    void highlightFunction2(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->sprite.setColor(se::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
    }


    void unhighlightFunction2(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((se::Button*)sender)->sprite.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
    }


    void startButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        menuSystem->changeMenu("Main");
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


    void resumeButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        ((BodyGame*)se::Engine::getCurrentScene())->resume();
    }


    void restartButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        menuSystem->changeMenu("UI");
        BodyGame* newScene = new BodyGame();
        se::Engine::changeScene(newScene);
    }


    void mainMenuButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        menuSystem->changeMenu("Main");
        se::Sprite background = se::Content::getSprite("flesh");
        MenuScene* newScene = new MenuScene(background);
        se::Engine::changeScene(newScene);
    }


    void highscoreButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        bc::GameData::loadScores();

        unsigned int offset = 0;
        if (((se::Button*)sender)->text.getText() == "Nerves")
            offset = 10;
        else if (((se::Button*)sender)->text.getText() == "Slime")
            offset = 20;
        else if (((se::Button*)sender)->text.getText() == "Pus")
            offset = 30;

        for (unsigned int i = 0; i < 10; ++i)
        {
            char number[3];
            _itoa(i, number, 10);
            ((se::UIText*)se::Engine::getMenu()->getElement("Highscores", "HighscoreName" + std::string(number)))->getText().setText(bc::GameData::scores[i + offset].name);

            char scoreText[16] = "";
            if (strcmp(bc::GameData::scores[i + offset].name, "   ") != 0)
                _itoa(bc::GameData::scores[i + offset].score, scoreText, 10);
            ((se::UIText*)se::Engine::getMenu()->getElement("Highscores", "Highscore" + std::string(number)))->getText().setText(scoreText);
        }

        menuSystem->changeMenu("Highscores");
    }


    void backButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        menuSystem->changeMenu("Main");
    }


    void nextLevelButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        std::string level = ((MenuData*)se::Engine::getMenu()->data)->levelName;

        if (level == "Flesh")
        {
            ((MenuData*)se::Engine::getMenu()->data)->levelName = "Nerves";
        }
        else if (level == "Nerves")
        {
            ((MenuData*)se::Engine::getMenu()->data)->levelName = "Slime";
        }
        if (level == "Slime")
        {
            ((MenuData*)se::Engine::getMenu()->data)->levelName = "Pus";
        }
        menuSystem->changeMenu("UI");
        BodyGame* newScene = new BodyGame();
        se::Engine::changeScene(newScene);
    }


    void characterButtonFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        if (((MenuData*)menuSystem->data)->currentChar < 3)
        {
            ((MenuData*)menuSystem->data)->playerName[((MenuData*)menuSystem->data)->currentChar] = *((se::Button*)sender)->text.getText().c_str();
            ++((MenuData*)menuSystem->data)->currentChar;
            ((se::UIText*)menuSystem->getElement("LevelEnd", "NameText"))->getText().setText("Your Name: " + std::string(((MenuData*)menuSystem->data)->playerName));
        }
    }


    void changeBackgroundFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
        std::string name = "flesh";
        std::string button = ((se::Button*)sender)->text.getText();
        if (button == "Nerves")
        {
            name = "nerves";
        }
        else if (button == "Slime")
        {
            name = "snot";
        }
        else if (button == "Pus")
        {
            name = "plus";
        }
        ((MenuScene*)se::Engine::getCurrentScene())->setBackground(se::Content::getSprite(name));
    }


    void saveScoreFunction(se::IMenuElement* sender, se::MenuSystem* menuSystem)
    {
		if (strcmp(((MenuData*)se::Engine::getMenu()->data)->playerName, "   ") != 0)
		{
			std::string level = ((MenuData*)se::Engine::getMenu()->data)->levelName;
			unsigned int offset = 0;

			if (level == "Nerves")
			{
				offset = 10;
			}
			else if (level == "Slime")
			{
				offset = 20;
			}
			if (level == "Pus")
			{
				offset = 30;
			}

			std::vector<bc::GameData::Highscore> tempVec(&bc::GameData::scores[offset], &bc::GameData::scores[offset + 10]);
			bc::GameData::Highscore newScore;
			memcpy(newScore.name, ((MenuData*)se::Engine::getMenu()->data)->playerName, sizeof(char) * 4);
			newScore.name[3] = '\0';
			newScore.score = bc::GameData::score;
			tempVec.push_back(newScore);
			std::sort(tempVec.begin(), tempVec.end(), [](const bc::GameData::Highscore& lhs, const bc::GameData::Highscore& rhs)
			{
				return lhs.score > rhs.score;
			});
			memcpy(&bc::GameData::scores[offset], &tempVec[0], sizeof(bc::GameData::Highscore) * 10);

			bc::GameData::saveScores();

			((MenuData*)se::Engine::getMenu()->data)->playerName[0] = ' ';
			((MenuData*)se::Engine::getMenu()->data)->playerName[1] = ' ';
			((MenuData*)se::Engine::getMenu()->data)->playerName[2] = ' ';
			((MenuData*)se::Engine::getMenu()->data)->playerName[3] = '\0';
			((MenuData*)se::Engine::getMenu()->data)->currentChar = 0;
			((se::UIText*)menuSystem->getElement("LevelEnd", "NameText"))->getText().setText("Your Name: ");
		}
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

        if (bc::Spawner::bossAlive)
        {
            highest = (int)(((MenuData*)menuSystem->data)->bossHealth * 100.0f);
            for (int i = 0; i < 100; ++i)
            {
                char number[3];
                _itoa(i, number, 10);
                ((se::UISprite*)menuSystem->getElement("UI", "Bossbar" + std::string(number)))->getSprite().setColor(i < highest ? se::Vector4(1.0f, 1.0f, 1.0f, 1.0f) : se::Vector4(1.0f, 1.0f, 1.0f, 0.0f));
            }
        }
    }
}