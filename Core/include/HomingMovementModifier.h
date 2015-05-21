#pragma once

#include "IModifier.h"

namespace bc
{
    class HomingMovementModifier : public IModifier
    {
    private:

        Entity* targetEntity;
        float speed;

    public:

        HomingMovementModifier(Entity* targetEntity, float speed);
        ~HomingMovementModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}