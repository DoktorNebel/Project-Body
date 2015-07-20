#pragma once

#include "IModifier.h"

namespace bc
{
    class ItemModifier : public IModifier
    {
    public:

        struct Effect
        {
            enum Type
            {
                Upgrade,
                Normal,
                Split,
                Curvy,
                Homing,
                Laser
            };
        };

    private:

        Effect::Type effect;

    public:

        ItemModifier(Effect::Type effect);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}