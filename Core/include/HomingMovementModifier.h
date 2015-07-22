#pragma once

#include "IModifier.h"

#include <vector>

namespace bc
{
    class HomingMovementModifier : public IModifier
    {
    private:

        Entity* targetEntity;
        std::vector<CollisionGroup::Type> targetGroups;
        se::Vector2 targetPoint;
        se::Vector2 direction;
        float speed;
        bool delayed;
        float maxTurnRate;

    public:

        HomingMovementModifier(std::vector<CollisionGroup::Type> targetGroups, float speed, bool delayed, float maxTurnRate, float startRotation);
        ~HomingMovementModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}