#include "ProgressBar.h"

#include "Engine.h"
#include "MathFunctions.h"

namespace se
{
    ProgressBar::ProgressBar()
    {

    }


    ProgressBar::ProgressBar(Sprite borderSprite, Sprite fillSprite, Vector2 position, FillDirection::Type fillDirection)
        : borderSprite(borderSprite)
        , fillSprite(fillSprite)
        , fillStatus(1.0f)
        , fillDirection(fillDirection)
    {
        this->borderSprite.setPosition(position);
        this->fillSprite.setPosition(position);
    }


    void ProgressBar::initialize(MenuSystem* menuSystem)
    {

    }


    void ProgressBar::update(float elapsedTime)
    {

    }


    void ProgressBar::draw()
    {
        Engine::draw(this->borderSprite);
        Engine::draw(this->fillSprite);
    }


    float ProgressBar::getFill()
    {
        return this->fillStatus;
    }


    void ProgressBar::setFill(float value)
    {
        value = se::Math::Clamp(0.0f, 1.0f, value);

        Rectangle* spriteRect = (Rectangle*)((char*)&this->fillSprite + sizeof(unsigned int));
        float* width = (float*)((char*)&this->fillSprite + sizeof(unsigned int) + sizeof(Rectangle) + sizeof(Vector2) * 2);
        float* height = (float*)((char*)&this->fillSprite + sizeof(unsigned int) + sizeof(Rectangle) + sizeof(Vector2) * 2 + sizeof(float));
        
        switch (this->fillDirection)
        {
        case FillDirection::LeftToRight:
            spriteRect->right = spriteRect->left + this->borderSprite.getWidth() * value;
            *width = this->borderSprite.getWidth() * value;
            this->fillSprite.setPosition(se::Vector2(this->borderSprite.getPosition().x - this->borderSprite.getWidth() / 2.0f + *width / 2.0f, this->borderSprite.getPosition().y));
            break;

        case FillDirection::RightToLeft:
            spriteRect->left = spriteRect->right - this->borderSprite.getWidth() * value;
            *width = this->borderSprite.getWidth() * value;
            this->fillSprite.setPosition(se::Vector2(this->borderSprite.getPosition().x + this->borderSprite.getWidth() / 2.0f - *width / 2.0f, this->borderSprite.getPosition().y));
            break;

        case FillDirection::TopToBottom:
            spriteRect->top = spriteRect->bottom - this->borderSprite.getHeight() * value;
            *height = this->borderSprite.getHeight() * value;
            this->fillSprite.setPosition(se::Vector2(this->borderSprite.getPosition().x, this->borderSprite.getPosition().y - this->borderSprite.getHeight() / 2.0f + *height / 2.0f));
            break;

        case FillDirection::BottomToTop:
            spriteRect->bottom = spriteRect->top + this->borderSprite.getHeight() * value;
            *height = this->borderSprite.getHeight() * value;
            this->fillSprite.setPosition(se::Vector2(this->borderSprite.getPosition().x, this->borderSprite.getPosition().y + this->borderSprite.getHeight() / 2.0f - *height / 2.0f));
            break;
        }

        this->fillStatus = value;
    }
}