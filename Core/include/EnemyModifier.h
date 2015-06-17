#pragma once

#include "IModifier.h"
#include "AnimatedSprite.h"

namespace bc
{
    class EnemyModifier : public IModifier
    {
    private:

        se::AnimatedSprite animatedSprite;
        se::Vector2 position;
        unsigned int score;
        float humanInfection;
        CollisionGroup::Type lastHit;

    public:

        bool golden;

    public:

        EnemyModifier(se::AnimatedSprite animatedSprite, unsigned int score, float humanInfection);
        ~EnemyModifier();

    public:

        virtual void onCreate();
        virtual void onUpdate(float elapsedTime);
        virtual void onHit(Entity* otherEntity, CollisionGroup::Type collisionGroup, se::Vector2 projectionVector, float projectionScalar);
    };
}