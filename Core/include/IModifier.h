#pragma once

#include "Collisiongroup.h"
#include "Vector2.h"

namespace bc
{
    class Entity;

    class IModifier
    {
    public:

        Entity* entity;

    public:

        virtual void onCreate() = 0;
        virtual void onUpdate(float elapsedTime) = 0;
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar) = 0;
    };
}