#pragma once

#include "IModifier.h"
#include <vector>

namespace bc
{
    class StickyShotModifier : public IModifier
    {
    private:

        std::vector<std::vector<Entity>>* entities;
        float radius;

    public:

        StickyShotModifier(std::vector<std::vector<Entity>>* entities);
        ~StickyShotModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}