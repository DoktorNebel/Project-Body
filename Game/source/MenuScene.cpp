#include "MenuScene.h"

namespace bg
{
    MenuScene::MenuScene(se::Sprite background)
        : background(background)
    {

    }


    MenuScene::~MenuScene()
    {

    }


    void MenuScene::initialize()
    {

    }


    void MenuScene::update(float elapsedTime)
    {

    }


    void MenuScene::draw()
    {
        se::Engine::draw(this->background);
    }


    void MenuScene::close()
    {

    }


    void MenuScene::setBackground(se::Sprite newBackground)
    {
        this->background = newBackground;
    }
}