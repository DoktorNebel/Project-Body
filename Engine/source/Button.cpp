#include "Button.h"

#include "Input.h"
#include "MenuInputActions.h"
#include "Engine.h"


namespace se
{
    Button::Button()
    {

    }


    Button::Button(Sprite sprite, Text text, bool useSpriteRect)
        : sprite(sprite)
        , text(text)
        , useSpriteRect(useSpriteRect)
    {

    }


    void Button::initialize(MenuSystem* menuSystem)
    {
        this->neighbours[LEFT_NEIGHBOUR] = 0;
        this->neighbours[RIGHT_NEIGHBOUR] = 0;
        this->neighbours[UP_NEIGHBOUR] = 0;
        this->neighbours[DOWN_NEIGHBOUR] = 0;

        this->eventNames.push_back("onPress");
        this->eventNames.push_back("onRelease");
    }


    void Button::update(float elapsedTime)
    {
        Rectangle spriteRect = this->useSpriteRect ? this->sprite.getRect() : this->text.getRect();
        if (!this->highlighted && spriteRect.contains(Input::getMousePos()))
        {
            Engine::getMenu()->highlight(this);
        }

        if ((this->highlighted && Input::actionPressed(InputAction::MenuConfirm)) || (spriteRect.contains(Input::getMousePos()) && Input::actionPressed(InputAction::MenuClick)))
        {
            this->pressed = true;
            this->callEvent("onPress");
        }

        if (this->pressed && (Input::actionReleased(InputAction::MenuConfirm) || Input::actionReleased(InputAction::MenuClick)))
        {
            this->pressed = false;
            this->callEvent("onRelease");
        }
    }


    void Button::draw()
    {
        se::Engine::draw(this->sprite);
        se::Engine::draw(this->text);
    }
}