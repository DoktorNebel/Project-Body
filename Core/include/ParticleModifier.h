#pragma once

#include "IModifier.h"
#include "Vector2.h"

namespace bc
{
    class ParticleModifier : public IModifier
    {
    private:

        se::Vector2 velocity;
        float lifeTime;
        float startLifeTime;

    public:

        ParticleModifier(se::Vector2(velocity), float lifeTime);
        ~ParticleModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}