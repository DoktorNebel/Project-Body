#pragma once

#include "IMenuElement.h"

namespace se
{
    class Button : public IMenuElement
    {
    private:

        Sprite sprite;
        Text text;
        bool pressed;

    public:

        Button();
        Button(Sprite sprite, Text text);


    public:

        virtual void initialize(MenuSystem* menuSystem);
        virtual void update(float elapsedTime);
        virtual void draw();
    };
}