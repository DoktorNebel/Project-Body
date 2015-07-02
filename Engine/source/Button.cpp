#include "Button.h"

#include "Input.h"
#include "MenuInputActions.h"
#include "Engine.h"


namespace se
{
    Button::Button()
    {

    }


    Button::Button(Sprite sprite, Text text)
        : sprite(sprite)
        , text(text)
    {

    }


    void Button::initialize(MenuSystem* menuSystem)
    {
        this->neighbours[LEFT_NEIGHBOUR] = 0;
        this->neighbours[RIGHT_NEIGHBOUR] = 0;
        this->neighbours[UP_NEIGHBOUR] = 0;
        this->neighbours[DOWN_NEIGHBOUR] = 0;

        this->eventNames.push_back("OnPress");
        this->eventNames.push_back("OnRelease");
        this->eventNames.push_back("OnHighlight");

        for (unsigned int i = 0; i < this->eventNames.size(); ++i)
        {
            this->events.push_back(MenuEvent(this, menuSystem));
        }
    }


    void Button::update(float elapsedTime)
    {
        Rectangle spriteRect = this->sprite.getRect();
        if (spriteRect.contains(Input::getMousePos()))
            this->highlight();

        if (this->highlighted && (Input::actionPressed(InputAction::MenuConfirm) || Input::actionPressed(InputAction::MenuClick)))
        {
            this->pressed = true;
            this->callEvent("OnPress");
        }

        if (this->pressed && (Input::actionReleased(InputAction::MenuConfirm) || Input::actionReleased(InputAction::MenuClick)))
        {
            this->pressed = false;
            this->callEvent("OnRelease");
        }
    }


    void Button::draw()
    {
        se::Engine::draw(this->sprite);
        se::Engine::draw(this->text);
    }
}