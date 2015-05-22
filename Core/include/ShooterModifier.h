#pragma once

#include "IModifier.h"

#include <vector>

namespace bc
{
    class ShooterModifier : public IModifier
    {
    private:

        std::vector<std::vector<Entity>>* entities;

    public:

        ShooterModifier(std::vector<std::vector<Entity>>* entities);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}