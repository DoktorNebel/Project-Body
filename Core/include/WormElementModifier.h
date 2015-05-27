#pragma once

#include "IModifier.h"

namespace bc
{
    class WormElementModifier : public IModifier
    {
    private:

        int elementNum;
        bool head;
        se::Vector2 spawnPos;
        WormElementModifier* nextElement;
        WormElementModifier* previousElement;
        bool spawned;
        bool stopped;

    public:

        WormElementModifier(bool head, int length, WormElementModifier* previousElement);

    public:

        void stop();
        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}