#pragma once

#include "IModifier.h"

#include "PlayerModifier.h"

namespace bc
{
    class LaserShootingModifier;

    class LaserModifier : public IModifier
    {
    public:

        struct LaserPart
        {
            enum Type
            {
                Bottom,
                Middle,
                Top
            };
        };

    private:

        LaserPart::Type part;
        float speed;
        PlayerModifier* player;
        se::Vector2 lastPlayerPos;
        float elapsedTime;
        se::Vector2 topPos;
        LaserModifier* previous;
        LaserShootingModifier* shooting;
        float damage;

    public:

        LaserModifier(LaserPart::Type part, LaserModifier* previous, LaserShootingModifier* shooting, float damage);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}