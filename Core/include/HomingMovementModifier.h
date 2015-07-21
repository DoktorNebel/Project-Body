#pragma once

#include "IModifier.h"

#include <vector>

namespace bc
{
    class HomingMovementModifier : public IModifier
    {
    private:

        Entity* targetEntity;
        std::vector<Entity>* targetEntities;
        se::Vector2 targetPoint;
        se::Vector2 direction;
        float speed;
        bool delayed;
        float maxTurnRate;

    public:

        HomingMovementModifier(Entity* targetEntity, float speed, bool delayed, float maxTurnRate);
        HomingMovementModifier(std::vector<Entity>* targetEntities, float speed, bool delayed, float maxTurnRate);
        ~HomingMovementModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}