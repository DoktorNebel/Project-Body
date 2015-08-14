#include "UISprite.h"

#include "Engine.h"

namespace se
{
    UISprite::UISprite()
    {

    }


    UISprite::UISprite(Sprite sprite, Vector2 position, float rotation, Vector2 scale, Vector4 color, float depth)
        : sprite(sprite)
    {
        this->sprite.setPosition(position);
        this->sprite.setRotation(rotation);
        this->sprite.setScale(scale);
        this->sprite.setColor(color);
        this->sprite.setDepth(depth);
    }


    void UISprite::initialize(MenuSystem* menuSystem)
    {

    }


    void UISprite::update(float elapsedTime)
    {

    }


    void UISprite::draw()
    {
        Engine::draw(this->sprite);
    }


    Sprite& UISprite::getSprite()
    {
        return this->sprite;
    }
}