#pragma once

#include "IModifier.h"
#include "Vector2.h"

namespace bc
{
    class ProjectileModifier : public IModifier
    {
    private:

        se::Vector2 velocity;
        float lifeTime;

    public:

        ProjectileModifier(se::Vector2(velocity), float lifeTime);
        ~ProjectileModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup);
    };
}