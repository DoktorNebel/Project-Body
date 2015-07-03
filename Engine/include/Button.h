#pragma once

#include "IMenuElement.h"

namespace se
{
    class Button : public IMenuElement
    {
    private:

        bool pressed;
        bool useSpriteRect;

    public:

        Sprite sprite;
        Text text;

    public:

        Button();
        Button(Sprite sprite, Text text, bool useSpriteRect);

    private:

        virtual void initialize(MenuSystem* menuSystem);
        virtual void update(float elapsedTime);
        virtual void draw();
    };
}