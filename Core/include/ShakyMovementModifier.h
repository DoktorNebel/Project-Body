#pragma once

#include "IModifier.h"

namespace bc
{
    class ShakyMovementModifier : public IModifier
    {
    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}