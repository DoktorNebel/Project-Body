#pragma once

#include "IModifier.h"

#include <vector>

namespace bc
{
    class PlayerShootingModifier : public IModifier
    {
    private:

        float stickyFireRate;
        float stickyFireCounter;
        std::vector<std::vector<Entity>>* entities;

    protected:

        int level;

    private:

        virtual void shoot(float elapsedTime) = 0;
        virtual void setLevel() = 0;

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
        void upgrade(int level = 0);
        void setEntities(std::vector<std::vector<Entity>>* entities);
        int getLevel();
    };
}