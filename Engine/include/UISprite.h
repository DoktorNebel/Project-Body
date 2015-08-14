#pragma once

#include "IMenuElement.h"

namespace se
{
    class UISprite : public IMenuElement
    {
    private:

        Sprite sprite;

    public:

        UISprite();
        UISprite(Sprite sprite, Vector2 position = Vector2(), float rotation = 0.0f, Vector2 scale = Vector2(1.0f, 1.0f), Vector4 color = Vector4(1.0f, 1.0f, 1.0f, 1.0f), float depth = 0.0f);

    public:

        virtual void initialize(MenuSystem* menuSystem);
        virtual void update(float elapsedTime);
        virtual void draw();
        Sprite& getSprite();
    };
}