#pragma once

#include "IModifier.h"

namespace bc
{
    class HomingMovementModifier : public IModifier
    {
    private:

        Entity* targetEntity;
        se::Vector2 targetPoint;
        float speed;
        bool delayed;

    public:

        HomingMovementModifier(Entity* targetEntity, float speed, bool delayed);
        ~HomingMovementModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}