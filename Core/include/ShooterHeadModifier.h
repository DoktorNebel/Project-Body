#pragma once

#include "IModifier.h"

#include <vector>

namespace bc
{
    class ShooterModifier;

    class ShooterHeadModifier : public IModifier
    {
    private:

        std::vector<std::vector<Entity>>* entities;
        float fireRate;
        float timer;
        ShooterModifier* shooter;

    public:

        ShooterHeadModifier(std::vector<std::vector<Entity>>* entities, ShooterModifier* shooter);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}