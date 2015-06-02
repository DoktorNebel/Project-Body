#pragma once

#include "IModifier.h"

#include "AnimatedSprite.h"

namespace bc
{
    class AnimationModifier : public IModifier
    {
    private:

        se::AnimatedSprite sprite;

    public:

        AnimationModifier(se::AnimatedSprite sprite);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}