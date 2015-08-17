#pragma once

#include "IMenuElement.h"

#include "Text.h"

namespace se
{
    class UIText : public IMenuElement
    {
    private:

        Text text;

    public:

        UIText();
        UIText(Text text);

    public:

        virtual void initialize(MenuSystem* menuSystem);
        virtual void update(float elapsedTime);
        virtual void draw();
        Text& getText();
    };
}