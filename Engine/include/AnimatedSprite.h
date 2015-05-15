#pragma once

#include <vector>
#include <string>
#include "Sprite.h"

namespace se
{
    class AnimatedSprite
    {
    private:

        std::vector<std::string> animationNames;
        std::vector<float> animationSpeeds;
        std::vector<std::vector<se::Sprite>> sprites;
        int currentAnimationIndex;
        int currentSpriteIndex;
        float animationTimer;
        Vector2 position;
        Vector2 size;
        float rotation;
        float depth;
        Vector4 color;
        bool finished;

    public:

        AnimatedSprite();
        ~AnimatedSprite();

    public:

        void addAnimation(std::string name);
        void addSprite(std::string animationName, se::Sprite sprite);
        void setSpeed(std::string animationName, float speed);
        bool changeAnimation(std::string animationName);
        std::string getCurrentAnimation();
        se::Sprite& getCurrentSprite();
        void move(Vector2 translation);
        Vector2 getPosition();
        void setPosition(Vector2 position);
        void scale(Vector2 factor);
        Vector2 getScale();
        void setScale(Vector2 scale);
        void rotate(float rotation);
        float getRotation();
        void setRotation(float rotation);
        void setDepth(float depth);
        Vector4 getColor();
        void setColor(Vector4 color);
        bool finishedAnimation();
        void update(float elapsedTime);
    };
}