#pragma once

#include "IModifier.h"

#include "PlayerModifier.h"

namespace bc
{
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

    public:

        LaserModifier(LaserPart::Type part);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}