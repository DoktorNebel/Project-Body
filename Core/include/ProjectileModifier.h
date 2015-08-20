#pragma once

#include "IModifier.h"
#include "Vector2.h"

namespace bc
{
    class ProjectileModifier : public IModifier
    {
    private:

        se::Vector2 direction;
        float speed;
        float lifeTime;
        float damage;

    public:

        ProjectileModifier(se::Vector2(velocity), float lifeTime, float damage = 1.0f);
        ~ProjectileModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}