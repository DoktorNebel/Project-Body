#include "UIText.h"

#include "Engine.h"

namespace se
{
    UIText::UIText()
    {

    }


    UIText::UIText(Text text)
        : text(text)
    {

    }


    void UIText::initialize(MenuSystem* menuSystem)
    {

    }


    void UIText::update(float elapsedTime)
    {

    }


    void UIText::draw()
    {
        se::Engine::draw(this->text);
    }


    Text& UIText::getText()
    {
        return this->text;
    }
}