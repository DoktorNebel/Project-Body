#include "AnimationModifier.h"

#include "Entity.h"

namespace bc
{
    AnimationModifier::AnimationModifier(se::AnimatedSprite sprite)
        : sprite(sprite)
    {

    }


    void AnimationModifier::onCreate()
    {

    }


    void AnimationModifier::onUpdate(float elapsedTime)
    {
        this->sprite.setPosition(this->entity->getSprite().getPosition());
        this->sprite.setRotation(this->entity->getSprite().getRotation());
        this->sprite.setScale(this->entity->getSprite().getScale());
        this->sprite.setColor(this->entity->getSprite().getColor());

        this->sprite.update(elapsedTime);

        this->entity->sprite = this->sprite.getCurrentSprite();
    }


    void AnimationModifier::onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar)
    {

    }
}