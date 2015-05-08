#include "AnimatedSprite.h"

namespace se
{
    AnimatedSprite::AnimatedSprite()
        : currentAnimationIndex(0)
        , currentSpriteIndex(0)
        , animationTimer(0.0f)
    {

    }


    AnimatedSprite::~AnimatedSprite()
    {

    }


    void AnimatedSprite::addAnimation(std::string name)
    {
        this->animationNames.push_back(name);
        this->animationSpeeds.push_back(0.5f);
        this->sprites.push_back(std::vector<se::Sprite>());
    }


    void AnimatedSprite::addSprite(std::string animationName, se::Sprite sprite)
    {
        int pos = std::find(this->animationNames.begin(), this->animationNames.end(), animationName) - this->animationNames.begin();
        this->sprites[pos].push_back(sprite);
    }


    void AnimatedSprite::setSpeed(std::string animationName, float speed)
    {
        int pos = std::find(this->animationNames.begin(), this->animationNames.end(), animationName) - this->animationNames.begin();
        this->animationSpeeds[pos] = speed;
    }


    void AnimatedSprite::changeAnimation(std::string animationName)
    {
        this->currentAnimationIndex = std::find(this->animationNames.begin(), this->animationNames.end(), animationName) - this->animationNames.begin();
    }


    std::string AnimatedSprite::getCurrentAnimation()
    {
        return this->animationNames[this->currentAnimationIndex];
    }


    se::Sprite& AnimatedSprite::getCurrentSprite()
    {
        this->sprites[this->currentAnimationIndex][this->currentSpriteIndex].setPosition(this->position);
        this->sprites[this->currentAnimationIndex][this->currentSpriteIndex].setRotation(this->rotation);
        this->sprites[this->currentAnimationIndex][this->currentSpriteIndex].setScale(this->size);
        this->sprites[this->currentAnimationIndex][this->currentSpriteIndex].setDepth(this->depth);
        this->sprites[this->currentAnimationIndex][this->currentSpriteIndex].setColor(this->color);
        return this->sprites[this->currentAnimationIndex][this->currentSpriteIndex];
    }


    void AnimatedSprite::move(Vector2 translation)
    {
        this->position += translation;
    }


    Vector2 AnimatedSprite::getPosition()
    {
        return this->position;
    }


    void AnimatedSprite::setPosition(Vector2 position)
    {
        this->position = position;
    }


    void AnimatedSprite::scale(Vector2 factor)
    {
        this->size *= factor;
    }


    Vector2 AnimatedSprite::getScale()
    {
        return this->size;
    }


    void AnimatedSprite::setScale(Vector2 scale)
    {
        this->size = scale;
    }


    void AnimatedSprite::rotate(float rotation)
    {
        this->rotation += rotation;
    }


    float AnimatedSprite::getRotation()
    {
        return this->rotation;
    }


    void AnimatedSprite::setRotation(float rotation)
    {
        this->rotation = rotation;
    }


    void AnimatedSprite::setDepth(float depth)
    {
        this->depth = depth;
    }


    Vector4 AnimatedSprite::getColor()
    {
        return this->color;
    }


    void AnimatedSprite::setColor(Vector4 color)
    {
        this->color = color;
    }


    bool AnimatedSprite::finishedAnimation()
    {
        return this->finished;
    }


    void AnimatedSprite::update(float elapsedTime)
    {
        this->animationTimer += elapsedTime;

        if (this->animationTimer >= this->animationSpeeds[this->currentAnimationIndex])
        {
            this->animationTimer = 0.0f;
            ++this->currentSpriteIndex;
            if (this->currentSpriteIndex >= this->sprites[this->currentAnimationIndex].size())
            {
                this->currentSpriteIndex = 0;
                this->finished = true;
            }
            else
            {
                this->finished = false;
            }
        }
    }
}