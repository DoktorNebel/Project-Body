#pragma once

#include "IMenuElement.h"

namespace se
{
    class Slider : public IMenuElement
    {
    private:

        bool pressed;
        float previousValue;
        float normalizedValue;
        float absoluteValue;
        float minValue;
        float maxValue;
        float stepWidth;
        se::Sprite sprite;
        se::Sprite sliderSprite;
        bool drawMinText;
        se::Text minText;
        bool drawMaxText;
        se::Text maxText;
        bool drawValueText;
        se::Text valueText;

    public:

        Slider();
        Slider(se::Sprite sprite, se::Sprite sliderSprite, se::Font* font, se::Vector2 position = se::Vector2(0.0f, 0.0f), float minValue = 0.0f, float maxValue = 100.0f, float stepWidth = 1.0f, float startValue = 1.0f, bool drawMinText = true, bool drawMaxText = true, bool drawValueText = true);
        ~Slider();

    private:

        virtual void initialize(MenuSystem* menuSystem);
        virtual void update(float elapsedTime);
        virtual void draw();
        void calculateValues();

    public:

        float getNormaliuedValue();
        float getAbsoluteValue();
        se::Vector2 getSliderPosition();
    };
}