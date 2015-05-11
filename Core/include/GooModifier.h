#pragma once

#include "IModifier.h"

#include <vector>
#include "Vector2.h"

namespace bc
{
    class GooModifier : public IModifier
    {
    private:

        std::vector<Entity*> otherEntities;
        float hitMarkerTime;
        float timer;
        se::Vector2 midPoint;

    public:

        GooModifier(std::vector<Entity*> otherEntities, se::Vector2 midPoint);
        ~GooModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup);
    };
}