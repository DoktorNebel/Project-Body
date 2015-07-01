#include "Button.h"

#include "Input.h"
#include "MenuInputActions.h"
#include "Engine.h"

#define LEFT_NEIGHBOUR 0
#define RIGHT_NEIGHBOUR 1
#define UP_NEIGHBOUR 2
#define DOWN_NEIGHBOUR 3

namespace se
{
    Button::Button()
    {
        this->initialize();
    }


    Button::Button(Sprite sprite, Text text)
        : sprite(sprite)
        , text(text)
    {
        this->initialize();
    }


    void Button::initialize()
    {
        this->neighbours[LEFT_NEIGHBOUR] = 0;
        this->neighbours[RIGHT_NEIGHBOUR] = 0;
        this->neighbours[UP_NEIGHBOUR] = 0;
        this->neighbours[DOWN_NEIGHBOUR] = 0;

        this->eventNames.push_back("OnPress");
        this->eventNames.push_back("OnRelease");
        this->eventNames.push_back("OnHighlight");
        this->eventNames.push_back("OnUpdate");

        this->events.resize(this->eventNames.size());
    }


    void Button::update(float elapsedTime)
    {

    }


    void Button::draw()
    {
        se::Engine::draw(this->sprite);
        se::Engine::draw(this->text);
    }


    void Button::setNeighbours(Button* left, Button* right, Button* up, Button* down)
    {
        this->neighbours[LEFT_NEIGHBOUR] = left;
        this->neighbours[RIGHT_NEIGHBOUR] = right;
        this->neighbours[UP_NEIGHBOUR] = up;
        this->neighbours[DOWN_NEIGHBOUR] = down;
    }
}