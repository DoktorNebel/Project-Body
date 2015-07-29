#pragma once

#include "IModifier.h"

#include <vector>

#include "PlayerModifier.h"

namespace bc
{
    class CoinModifier : public IModifier
    {
    private:

        std::vector<Entity>* players;
        bool player;
        se::Vector2 velocity;
        unsigned int score;
        float timer;

    public:

        CoinModifier(unsigned int score);

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}