#pragma once

#include "IMenuElement.h"

namespace se
{
    class ProgressBar : public IMenuElement
    {
    public:

        struct FillDirection
        {
            enum Type
            {
                LeftToRight,
                RightToLeft,
                TopToBottom,
                BottomToTop
            };
        };

    private:

        Sprite borderSprite;
        Sprite fillSprite;
        float fillStatus;
        FillDirection::Type fillDirection;

    public:

        ProgressBar();
        ProgressBar(Sprite borderSprite, Sprite fillSprite, Vector2 position = Vector2(), FillDirection::Type fillDirection = FillDirection::LeftToRight);

    private:

        virtual void initialize(MenuSystem* menuSystem);
        virtual void update(float elapsedTime);
        virtual void draw();

    public:

        float getFill();
        void setFill(float value);
    };
}