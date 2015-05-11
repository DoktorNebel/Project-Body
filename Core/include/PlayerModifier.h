#pragma once

#include "IModifier.h"
#include <vector>

namespace bc
{
    class PlayerModifier : public IModifier
    {
    private:

        float speed;
        float fireRate;
        float fireCounter;
        std::vector<std::vector<Entity>>* entities;

    public:

        PlayerModifier(std::vector<std::vector<Entity>>* entities);
        ~PlayerModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup);
    };
}