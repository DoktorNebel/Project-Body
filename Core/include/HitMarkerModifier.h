#pragma once

#include "IModifier.h"

namespace bc
{
    class HitMarkerModifier : public IModifier
    {
    private:

        float hitMarkerTime;
        float timer;

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}