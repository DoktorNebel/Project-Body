#pragma once

#include "IModifier.h"
#include "Vector2.h"

namespace bc
{
    class GooModifier;

    class GooParticleModifier : public IModifier
    {
    private:

        GooModifier* modifier;
        se::Vector2 prevMidPoint;
        float minSize;
        float maxSize;
        float scaleSpeed;
        float rotationSpeed;

    public:

        GooParticleModifier(GooModifier* modifier);
        ~GooParticleModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}