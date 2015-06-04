#pragma once

#include "IModifier.h"

namespace bc
{
    class BossModifier;

    class BossPartModifier : public IModifier
    {
    private:

        BossModifier* boss;

    public:

        int id;

    public:

        BossPartModifier(BossModifier* boss);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}