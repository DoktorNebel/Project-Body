#pragma once

#include "IModifier.h"

#include <vector>

#include "AnimatedSprite.h"

namespace bc
{
    class PlayerModifier : public IModifier
    {
    private:

        float speed;
        se::AnimatedSprite sprite;

    public:

        PlayerModifier();
        ~PlayerModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}