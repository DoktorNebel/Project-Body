#include "Slider.h"

#include "Engine.h"
#include "Input.h"
#include "MenuInputActions.h"
#include "MathFunctions.h"

namespace se
{
    Slider::Slider()
    {

    }


    Slider::Slider(se::Sprite sprite, se::Sprite sliderSprite, se::Font* font, se::Vector2 position, float minValue, float maxValue, float stepWidth, float startValue, bool drawMinText, bool drawMaxText, bool drawValueText)
        : pressed(false)
        , previousValue(startValue)
        , normalizedValue(startValue)
        , absoluteValue(Math::Lerp(minValue, maxValue, startValue))
        , minValue(minValue)
        , maxValue(maxValue)
        , stepWidth(stepWidth)
        , sprite(sprite)
        , sliderSprite(sliderSprite)
        , drawMinText(drawMinText)
        , minText(font)
        , drawMaxText(drawMaxText)
        , maxText(font)
        , drawValueText(drawValueText)
        , valueText(font)
    {
        this->sprite.setPosition(position);
        this->sliderSprite.setPosition(se::Vector2(-this->sprite.getWidth() * this->sprite.getScale().x / 2.0f + this->normalizedValue * this->sprite.getWidth() * this->sprite.getScale().x, this->sprite.getPosition().y));
        this->calculateValues();
    }


    Slider::~Slider()
    {

    }


    void Slider::initialize(MenuSystem* menuSystem)
    {
        this->eventNames.push_back("onPress");
        this->eventNames.push_back("onRelease");
        this->eventNames.push_back("onValueChange");
    }


    void Slider::update(float elapsedTime)
    {
        Rectangle spriteRect = this->sprite.getRect();
        se::Vector2 mousePos = Input::getMousePos();

        if (!this->highlighted && spriteRect.contains(mousePos))
        {
            Engine::getMenu()->highlight(this);
        }

        if ((this->highlighted && Input::actionPressed(InputAction::MenuConfirm)) || (spriteRect.contains(Input::getMousePos()) && Input::actionPressed(InputAction::MenuClick)))
        {
            this->pressed = true;
            this->callEvent("onPress");
        }

        if (this->pressed)
        {
            if (Input::getActionValue(InputAction::MenuClick) > 0.0f)
            {
                se::Vector2 pos(mousePos.x, this->sprite.getPosition().y);
                if (pos.x < this->sprite.getPosition().x - this->sprite.getWidth() * this->sprite.getScale().x / 2.0f)
                    pos.x = this->sprite.getPosition().x - this->sprite.getWidth() * this->sprite.getScale().x / 2.0f;

                if (pos.x > this->sprite.getPosition().x + this->sprite.getWidth() * this->sprite.getScale().x / 2.0f)
                    pos.x = this->sprite.getPosition().x + this->sprite.getWidth() * this->sprite.getScale().x / 2.0f;

                while (this->sliderSprite.getPosition().x - pos.x < 0.0f)
                    this->sliderSprite.move(se::Vector2(this->stepWidth * this->sprite.getWidth() * this->sprite.getScale().x, 0.0f));

                while (this->sliderSprite.getPosition().x - pos.x > 0.0f)
                    this->sliderSprite.move(se::Vector2(-this->stepWidth * this->sprite.getWidth() * this->sprite.getScale().x, 0.0f));
            }
            else
            {
                if (Input::actionPressed(InputAction::MenuLeft))
                {
                    this->sliderSprite.move(se::Vector2(-this->stepWidth * this->sprite.getWidth() * this->sprite.getScale().x, 0.0f));
                }
                if (Input::actionPressed(InputAction::MenuRight))
                {
                    this->sliderSprite.move(se::Vector2(this->stepWidth * this->sprite.getWidth() * this->sprite.getScale().x, 0.0f));
                }
            }

            this->calculateValues();

            if (this->normalizedValue != this->previousValue)
                this->callEvent("onValueChange");
            this->previousValue = normalizedValue;

            if (Input::actionPressed(InputAction::MenuConfirm) || Input::actionReleased(InputAction::MenuClick))
            {
                this->pressed = false;
                this->callEvent("onRelease");
            }
        }
    }


    void Slider::draw()
    {
        se::Engine::draw(this->sprite);
        se::Engine::draw(this->sliderSprite);
        if (this->drawMinText)
            se::Engine::draw(this->minText);
        if (this->drawMaxText)
            se::Engine::draw(this->maxText);
        if (this->drawValueText)
            se::Engine::draw(this->valueText);
    }


    void Slider::calculateValues()
    {
        float distance = this->sliderSprite.getPosition().x - (this->sprite.getPosition().x - this->sprite.getWidth() * this->sprite.getScale().x / 2);
        this->normalizedValue = distance / (this->sprite.getWidth() * this->sprite.getScale().x);
        this->absoluteValue = Math::Lerp(this->minValue, this->maxValue, this->normalizedValue);
        this->valueText.setPosition(this->sliderSprite.getPosition() + se::Vector2(0.0f, this->sliderSprite.getHeight() * this->sliderSprite.getScale().y / 2.0f + this->valueText.getHeight() * this->valueText.getScale().y / 2.0f));
        char valueString[16];
        _itoa((int)this->absoluteValue, valueString, 10);
        this->valueText.setText(valueString);
    }


    float Slider::getNormaliuedValue()
    {
        return this->normalizedValue;
    }


    float Slider::getAbsoluteValue()
    {
        return this->absoluteValue;
    }


    se::Vector2 Slider::getSliderPosition()
    {
        return this->sliderSprite.getPosition();
    }
}